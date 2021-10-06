SELECT AVG( songs.energy) FROM songs JOIN artists ON songs.artist_id = artists.id AND artists.name = "Drake"
