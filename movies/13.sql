-- first find what Kevin Bacon starred in

SELECT name FROM people INNER JOIN stars ON stars.person_id = people.id INNER JOIN movies ON movies.id = stars.movie_id WHERE movies.title IN (SELECT title FROM movies INNER JOIN stars ON stars.movie_id = movies.id INNER JOIN people ON stars.person_id = people.id WHERE people.name = 'Kevin Bacon' AND people.birth = 1958) AND people.name != 'Kevin Bacon';




