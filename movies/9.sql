SELECT DISTINCT name FROM people
    INNER JOIN stars ON people.id = stars.person_id
    INNER JOIN movies ON stars.movie_id = movies.id
    WHERE year = 2004
    ORDER BY birth;