#!/bin/bash
mkdir -p files/out
<../Makefile cat > "files/out/test00_out"

<../Makefile grep -v z | cat | wc -l > "files/out/test01_out"

lss | ls | cat > "files/out/test02_out"

ls | lss | cat > "files/out/test03_out"

chmod 000 Makefile | <Makefile cat | ls -a > "files/out/test04_out"

chmod 664 Makefile | <Makefile cat | ls -a > "files/out/test05_out"

./ls > "files/out/test06_out"

../bin/ls > "files/out/test07_out"

/bin/ls > "files/out/test08_out"

ping 8.8.8.8 | head -3 | ls > "files/out/test09_out"

uahsuah | iajsiaj | aijsiaj | aijsiajsi | /bin/ls > "files/out/test10_out"

/bin/ls|/bin/cat |/bin/cat|/bin/cat > "files/out/test11_out"
