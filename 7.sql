SELECT title, rating FROM movies
JOIN ratings
ON movies.id = ratings.movie_id
WHERE year = 2010 AND rating IS NOT '\\N'
ORDER BY rating DESC, title ASC;