printf "\x1b[32m need:\n\x1b[0m"
ls $1 > need.txt
printf "\x1b[33m mine:\n\x1b[0m"
./ft_ls $1 > mine.txt
diff -U3 mine.txt need.txt
