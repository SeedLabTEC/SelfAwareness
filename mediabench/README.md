
  ./djpeg -dct int -ppm -outfile testout.ppm  <img>.jpg
  ./djpeg -dct int -bmp -colors 256 -outfile testout.bmp  <img>.jpg
  ./cjpeg -dct int -outfile testout.jpg  <img>.ppm
  ./djpeg -dct int -ppm -outfile testoutp.ppm <img>.jpg
  ./cjpeg -dct int -progressive -opt -outfile testoutp.jpg <img>.ppm
  ./jpegtran -outfile testoutt.jpg <img>.jpg