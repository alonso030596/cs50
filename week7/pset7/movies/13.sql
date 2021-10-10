SELECT
    COUNT(name)
    FROM
    people
    WHERE
    name !="Kevin Bacon"
    AND
    id
    IN(
        SELECT 
            DISTINCT(person_id)
            FROM 
            stars
            WHERE 
            movie_id
            IN(
                SELECT
                    movie_id 
                    FROM 
                    stars
                    JOIN
                    people 
                    ON 
                    people.id = stars.person_id 
                    WHERE 
                    people.name = "Kevin Bacon" AND people.birth = 1958))
