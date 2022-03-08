-- Write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.

SELECT name FROM people WHERE id IN
(SELECT person_id FROM stars WHERE movie_id IN
(SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Kevin Bacon")))
EXCEPT
SELECT name FROM people WHERE name = "Kevin Bacon";