import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    """Show portfolio of stocks"""
    if request.method == "GET":
        # get username
        dictUser = db.execute("SELECT username FROM users WHERE id = ?", session['user_id'])  # returns a list of dictionary
        user = dictUser[0]["username"]
        # get all info from purchased data table
        dictInfo = db.execute("SELECT stocks,shares,price,total FROM purchased WHERE users = ?", user)
        # get cash total from purchased data table
        dictCash = db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])
        cash = dictCash[0]["cash"]
        # get grand total from purchased data table
        # maybe the USD conversion in the buy route when INSERTING is making it so that the dollars won't total
        dict_grandTotal = db.execute("SELECT SUM(total) FROM purchased")  # produces a dictionary
        grandTotal = dict_grandTotal[0]["SUM(total)"]
        if grandTotal == None:
            grandTotal = 0
        return render_template("index.html", dictInfo=dictInfo, cash=cash, grandTotal=grandTotal)
    else:
        # cash user wants to add from submitting html form
        addCash = request.form.get("cash")
        # pulling the existing cash in user's bank
        dictCash = db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])
        cash = dictCash[0]["cash"]
        # updating user's existing cash and added cash
        updatedBank = int(addCash) + int(cash)
        # updating SQL table with updated cash value
        db.execute("UPDATE users SET cash = ? WHERE id = ?", updatedBank, session['user_id'])
        return redirect("/")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    dictUser = db.execute("SELECT username FROM users WHERE id = ?", session['user_id'])  # returns a list of dictionary
    user = dictUser[0]["username"]
    dictCash = db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])
    cash = dictCash[0]["cash"]

    if request.method == "GET":
        return render_template("buy.html", user=user, cash=cash)

    else:

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        symbolInfo = lookup(symbol)

        try:
            shares = int(shares)
        except:
            return apology("Please enter a valid number")

        if not symbol:
            return apology("Please enter a symbol")
        if int(shares) < 0:
            return apology("Please enter a valid number")
        elif symbolInfo == None:
            return apology("Incorrect symbol")
        else:
            price = symbolInfo["price"]
            # deduct money from the user's bank
            updatedBank = cash - (int(shares) * price)
            if updatedBank > 0:
                totalValue = int(shares) * price
                db.execute("INSERT INTO purchased (stocks, shares, price, users, total) VALUES (?,?,?,?,?)",
                           symbol, shares, price, user, totalValue)
                db.execute("UPDATE users SET cash = ? WHERE id = ?", updatedBank, session['user_id'])
            else:
                return apology("Insufficient Funds")

    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    if request.method == "GET":
        # get username
        dictUser = db.execute("SELECT username FROM users WHERE id = ?", session['user_id'])  # returns a list of dictionary
        user = dictUser[0]["username"]
        # get all info from purchased data table
        dictInfo = db.execute("SELECT stocks,shares,price,total FROM purchased WHERE users = ?", user)
        # get cash total from purchased data table
        dictCash = db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])
        cash = dictCash[0]["cash"]
        # get grand total from purchased data table
        # maybe the USD conversion in the buy route when INSERTING is making it so that the dollars won't total
        dict_grandTotal = db.execute("SELECT SUM(total) FROM purchased")  # produces a dictionary
        grandTotal = dict_grandTotal[0]["SUM(total)"]
        if grandTotal == None:
            grandTotal = 0
        return render_template("index.html", dictInfo=dictInfo, cash=cash, grandTotal=grandTotal)
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        symbolInfo = lookup(symbol)  # produces a dictionary
        if symbolInfo == None:
            return apology("Incorrect Symbol")
        return render_template("quoted.html", symbolInfo=symbolInfo)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    username = request.form.get("username")
    password = request.form.get("password")
    confirmation = request.form.get("confirmation")

    if request.method == "GET":
        return render_template("register.html")
    else:
        if not username:
            return apology("Please enter a username")
        if not password:
            return apology("Please enter a password")
        if password != confirmation:
            return apology("Passwords do not match")

        usernames = db.execute("SELECT username FROM users")
        # usernames is a list of dictionaries

        storeNames = []  # empty list to hold usernames
        for i in range(len(usernames)):
            storeNames.append(usernames[i]["username"])

        if username not in storeNames:
            hashed = generate_password_hash(password)
            db.execute("INSERT INTO users (username, hash) VALUES (?,?)", username, hashed)
        else:
            return apology("username taken")

    return redirect("/login")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    dictUser = db.execute("SELECT username FROM users WHERE id = ?", session['user_id'])
    # returns a list of dictionary
    user = dictUser[0]["username"]
    # get all info from purchased data table
    dictInfo = db.execute("SELECT stocks,shares,price,total FROM purchased WHERE users = ?", user)
    dictCash = db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])
    cash = dictCash[0]["cash"]

    if request.method == "GET":
        return render_template("sell.html", dictInfo=dictInfo)

    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        shares = int(shares)
        symbolInfo = lookup(symbol)  # looking up a symbol to get a price

        if symbolInfo == None:
            return apology("Please enter a symbol")

        try:
            int(shares) < 0
        except ValueError:
            return apology("Please enter a valid number")

        price = symbolInfo["price"]  # get price info

        dict_sharesowned = db.execute("SELECT shares FROM purchased WHERE stocks = ? AND users = ?", symbol, user)
        sharesowned = dict_sharesowned[0]["shares"]

        # holding total of current stock
        dict_holdingTotal = db.execute("SELECT total FROM purchased WHERE stocks = ? AND users = ?", symbol, user)
        holdingTotal = dict_holdingTotal[0]["total"]

        # need to double check that the user has that many shares

        if shares <= sharesowned:
            # put money into the user's bank
            updatedBank = cash + (shares * price)
            totalValue = shares * price
            db.execute("INSERT INTO sold (stock, shares, price, user, total) VALUES (?,?,?,?,?)",
                       symbol, shares, price, user, totalValue)
            # using the below to update the purchased table
            newSharesOwned = sharesowned - shares
            newtotalValue = holdingTotal - totalValue
            db.execute("UPDATE purchased SET shares = ?, total = ? WHERE stocks = ?", newSharesOwned, newtotalValue, symbol)
            if newSharesOwned == 0:
                db.execute("DELETE FROM purchased WHERE shares = 0")
            # this updates the total cash the user has
            db.execute("UPDATE users SET cash = ? WHERE id = ?", updatedBank, session['user_id'])
            return redirect("/")
        else:
            return apology("Not enough shares to sell")

