SELECT title FROM movies
    INNER JOIN stars ON stars.movie_id = movies.id
    INNER JOIN people ON people.id = stars.person_id
    INNER JOIN ratings on ratings.movie_id = movies.id
    WHERE people.name = 'Chadwick Boseman'
    ORDER BY rating DESC LIMIT 5;