## Photo sorter

Photo sorter is a program that sorts photo files.

At this point, it recursively iterates though files in a directory, identifies photo files from Sony RX-100 M3 and Sony Xperia XZ2 Compact and copies them into another directory, sorted into subdirecties by date and renamed using time, camera id and the photo number assigned by the camera.

It uses libexiv2 for reading meta data from the photo files.
