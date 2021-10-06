SELECT songs.name, artists.name FROM songs JOIN artists ON songs.artist_id = artists.id AND songs.name LIKE "%feat.%" 
