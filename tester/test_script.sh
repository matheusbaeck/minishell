#!/bin/bash
mkdir -p files/original
<../Makefile cat > "files/original/test00_out"
#!/bin/bash
mkdir -p files/original
<../Makefile grep -v z | cat | wc -l > "files/original/test01_out"
#!/bin/bash
mkdir -p files/original
lss | ls | cat > "files/original/test02_out"
#!/bin/bash
mkdir -p files/original
ls | lss | cat > "files/original/test03_out"
#!/bin/bash
mkdir -p files/original
chmod 000 Makefile | <Makefile cat | ls -a > "files/original/test04_out"
#!/bin/bash
mkdir -p files/original
chmod 664 Makefile | <Makefile cat | ls -a > "files/original/test05_out"
#!/bin/bash
mkdir -p files/original
./ls > "files/original/test06_out"
#!/bin/bash
mkdir -p files/original
../bin/ls > "files/original/test07_out"
#!/bin/bash
mkdir -p files/original
/bin/ls > "files/original/test08_out"
#!/bin/bash
mkdir -p files/original
ping 8.8.8.8 | head -3 | ls > "files/original/test09_out"
#!/bin/bash
mkdir -p files/original
uahsuah | iajsiaj | aijsiaj | aijsiajsi | /bin/ls > "files/original/test10_out"
#!/bin/bash
mkdir -p files/original
/bin/ls|/bin/cat |/bin/cat|/bin/cat > "files/original/test11_out"
#!/bin/bash
mkdir -p files/original
ls | <..Makefile cat | cat | <ls >> out > "files/original/test12_out"
#!/bin/bash
mkdir -p files/original
13 > "files/original/test_out"
#!/bin/bash
mkdir -p files/original
out > "files/original/cat_out"
#!/bin/bash
mkdir -p files/original
rm out | cat /dev/random | head -100 | wc -l > "files/original/test14_out"
