"""
Tic Tac Toe Player
"""

import math
import copy

X = "X"
O = "O"
EMPTY = None


def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY]]


def player(board):
    """
    Returns player who has the next turn on a board.
    """

    player = None

    # if board is in initial state, then the X player gets to start.
    if board == initial_state():
        player = X
        return player
    elif player == X:
        player = O
        return player
    elif player == O:
        player = X
        return player


def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """
    # if the cell of board is empty then there is possibility for an action

    # declare empty set
    possible_actions = set()

    # for each row in tic tac toe list
    for i in range(3):
        # for each cell in tic tac toe list
        for j in range(3):
            if board[i][j] == "EMPTY":
                possible_actions.add()

    return possible_actions


def result(board, action):
    """
    Returns the board that results from making move (i, j) on the board.
    """
    # create a deepcopy of the board
    new_board = copy.deepcopy(board)

    # action is a tuple and needs to be broken out
    # the i coordinate in action will be stored in i and the j coordinate in action will be stored in j
    i, j = action

    # go to the coordinate on the board and if that cell is empty, make it equal to player
    if new_board[i][j] == "EMPTY":
        new_board[i][j] = player

    return new_board


def winner(board):
    """
    Returns the winner of the game, if there is one.
    """
    # checking if there is a match horizontally
    if board[0][0] == board[0][1] == board[0][2]:
        if board[0][0] == "X":
            return X
        elif board[0][0] == "O":
            return O
    elif board[1][0] == board[1][1] == board[1][2]:
        if board[1][0] == "X":
            return X
        elif board[1][0] == "O":
            return O
    elif board[2][0] == board[2][1] == board[2][2]:
        if board[2][0] == "X":
            return X
        elif board[2][0] == "O":
            return O

    # checking if there is a match vertically
    elif board[0][0] == board[1][0] == board[2][0]:
        if board[0][0] == "X":
            return X
        elif board[0][0] == "O":
            return O
    elif board[0][1] == board[1][1] == board[2][1]:
        if board[0][1] == "X":
            return X
        elif board[0][1] == "O":
            return O
    elif board[0][2] == board[1][2] == board[2][2]:
        if board[0][2] == "X":
            return X
        elif board[0][2] == "O":
            return O

    # checking if there's a match diagonally
    elif board[0][0] == board[1][1] == board[2][2]:
        if board[0][0] == "X":
            return X
        elif board[0][0] == "O":
            return O
    elif board[0][2] == board[1][1] == board[2][0]:
        if board[0][2] == "X":
            return X
        elif board[0][2] == "O":
            return O
    else:
        return None

    # THERE'S PROBABLY AN EASIER WAY TO DO THIS

    # RETURN NONE IF THERE IS NOT WINNER


def terminal(board):
    """
    Returns True if game is over, False otherwise.
    """
    # if the board isn't empty and there is not winner, then game is over
    # or if there is a winner, game is over
    if "EMPTY" not in board and winner(board) == None:
        return True
    elif winner(board) != None:
        return True
    else:
        return False


def utility(board):
    """
    Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
    """
    if winner(board) == X:
        return 1
    elif winner(board) == O:
        return -1
    else:
        return 0



def minimax(board):
    """
    Returns the optimal action for the current player on the board.
    """
    # the min and max value functions will keep calling each other, making a move until it reaches the base case terminal state

    bestmove = None

    def max_value(board):
        v = float(-inf)
        if terminal(board) == True:
            return utility(board)
        else:
            for action in actions(board):
                v = max(v, min_value(result(board,action)))
                # need to find a way to store the best action in a variable
                return v

    def min_value(board):
        v = float(inf)
        if terminal(board) == True:
            return utility(board)
        else:
            for action in actions(board):
                v = min(v, max_value(result(board,action)))
                return v

    # if the turn is X, we're trying to maximize value
    if player(board) == X:
        max_value(board)

    # if the turn is O, we're trying to minimize the value
    if player(board) == O:
        min_value(board)


