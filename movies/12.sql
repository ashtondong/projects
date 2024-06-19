SELECT title FROM movies INNER JOIN stars ON stars.movie_id = movies.id INNER JOIN people ON people.id = stars.person_id
    WHERE people.name = 'Johnny Depp' OR people.name = 'Helena Bonham Carter'
    GROUP BY title
    HAVING COUNT(title) = 2;

-- get helena's movie titles
-- get johnny's movie titles
-- take the titles that they have matching



