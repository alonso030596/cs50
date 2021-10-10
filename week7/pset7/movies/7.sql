SELECT movies.title, ratings.rating FROM movies JOIN ratings ON movies.id = ratings.movie_id WHERE movies.year = 2012 AND ratings.rating ORDER by ratings.rating DESC, movies.title
