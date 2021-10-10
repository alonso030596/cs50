SELECT DISTINCT(people.name) FROM
movies JOIN ratings ON movies.id = ratings.movie_id
JOIN directors ON movies.id = directors.movie_id
JOIN people ON people.id = directors.person_id
WHERE ratings.rating >= 9

