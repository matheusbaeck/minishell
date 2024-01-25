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
cat /dev/random | head -100 | wc -l > "files/original/test13_out"
#!/bin/bash
mkdir -p files/original
/bin/echo ""$?"" done > "files/original/test14_out"
#!/bin/bash
mkdir -p files/original
/bin/echo $?"42" done > "files/original/test15_out"
#!/bin/bash
mkdir -p files/original
/bin/echo ''$?''"42" > "files/original/test16_out"
#!/bin/bash
mkdir -p files/original
/bin/echo '"$USER"' > "files/original/test17_out"
#!/bin/bash
mkdir -p files/original
/bin/echo "'$USER'" > "files/original/test18_out"
#!/bin/bash
mkdir -p files/original
/bin/echo ""'$USER'""  > "files/original/test19_out"
#!/bin/bash
mkdir -p files/original
/bin/echo '"'$USER'"'  > "files/original/test20_out"
#!/bin/bash
mkdir -p files/original
/bin/echo "''$USER''" > "files/original/test21_out"
#!/bin/bash
mkdir -p files/original
/bin/echo "''$USER''" > "files/original/test22_out"
#!/bin/bash
mkdir -p files/original
/bin/echo '"'  "$USER"   '"' > "files/original/test23_out"
#!/bin/bash
mkdir -p files/original
/bin/echo $"HOME"$USER > "files/original/test24_out"
#!/bin/bash
mkdir -p files/original
/bin/echo $"HOM"E$USER > "files/original/test25_out"
#!/bin/bash
mkdir -p files/original
/bin/echo "exit_code ->$? user ->$USER home -> $HOME" > "files/original/test26_out"
#!/bin/bash
mkdir -p files/original
/bin/echo $"HOME" > "files/original/test27_out"
#!/bin/bash
mkdir -p files/original
/bin/echo $"42$" > "files/original/test28_out"
#!/bin/bash
mkdir -p files/original
/bin/echo "$ " > "files/original/test29_out"
#!/bin/bash
mkdir -p files/original
/bin/echo hi >./outfiles/outfile01 | /bin/echo bye  > "files/original/test30_out"
#!/bin/bash
mkdir -p files/original
/bin/echo <123 <456 hi | /bin/echo 42  > "files/original/test31_out"
#!/bin/bash
mkdir -p files/original
/bin/echo '$=' > "files/original/test32_out"
#!/bin/bash
mkdir -p files/original
/bin/echo '$ ' > "files/original/test33_out"
#!/bin/bash
mkdir -p files/original
/bin/echo "$?" > "files/original/test34_out"
#!/bin/bash
mkdir -p files/original
/bin/echo '$?' > "files/original/test35_out"
#!/bin/bash
mkdir -p files/original
/bin/echo "'$?'" > "files/original/test36_out"
#!/bin/bash
mkdir -p files/original
/bin/echo \$USER > "files/original/test37_out"
#!/bin/bash
mkdir -p files/original
/bin/echo \\$USER > "files/original/test38_out"
#!/bin/bash
mkdir -p files/original
/bin/echo \\\$USER > "files/original/test39_out"
#!/bin/bash
mkdir -p files/original
/bin/echo \\\\$USER > "files/original/test40_out"
#!/bin/bash
mkdir -p files/original
/bin/echo \\\\\$USER > "files/original/test41_out"
#!/bin/bash
mkdir -p files/original
/bin/echo \\\\\\\\\$USER > "files/original/test42_out"
#!/bin/bash
mkdir -p files/original
/bin/echo \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\$USER \$PATH \\$PWD à voir.... toutes ces contrebarres... > "files/original/test43_out"
#!/bin/bash
mkdir -p files/original
/bin/echo "cat lol.c | cat > lol.c" > "files/original/test44_out"
#!/bin/bash
mkdir -p files/original
/bin/echo "cat lol.c '|' cat > lol.c" > "files/original/test45_out"
#!/bin/bash
mkdir -p files/original
/bin/echo '$USER' "$USER" "text  ' text" > "files/original/test46_out"
#!/bin/bash
mkdir -p files/original
/bin/echo $USER =intergalaktikus miaf*szomez  > "files/original/test47_out"
#!/bin/bash
mkdir -p files/original
/bin/echo -n"-n" bonjour > "files/original/test48_out"
#!/bin/bash
mkdir -p files/original
/bin/echo "'$USER'" > "files/original/test49_out"
#!/bin/bash
mkdir -p files/original
/bin/echo " '$USER' " > "files/original/test50_out"
#!/bin/bash
mkdir -p files/original
/bin/echo text"$USER" > "files/original/test51_out"
#!/bin/bash
mkdir -p files/original
/bin/echo text"'$USER'" ' $USER '         > "files/original/test52_out"
#!/bin/bash
mkdir -p files/original
/bin/echo "text"   "$USER"    "$USER" > "files/original/test53_out"
#!/bin/bash
mkdir -p files/original
/bin/echo '              $USER          ' > "files/original/test54_out"
#!/bin/bash
mkdir -p files/original
/bin/echo ''''''''''$USER'''''''''' > "files/original/test55_out"
#!/bin/bash
mkdir -p files/original
/bin/echo """"""""$USER"""""""" > "files/original/test56_out"
#!/bin/bash
mkdir -p files/original
/bin/echo '""""""""$USER""""""""' 			 > "files/original/test57_out"
#!/bin/bash
mkdir -p files/original
/bin/echo ""'""""""$USER""""""'"" 			 > "files/original/test58_out"
#!/bin/bash
mkdir -p files/original
/bin/echo """"""""'$USER'""""""""''		 > "files/original/test59_out"
#!/bin/bash
mkdir -p files/original
/bin/echo """""""'"$USER"'"""""""			 > "files/original/test60_out"
#!/bin/bash
mkdir -p files/original
/bin/echo """"""'""$USER""'""""""  > "files/original/test61_out"
#!/bin/bash
mkdir -p files/original
/bin/echo ""'""'""""$USER""""'""'"" > "files/original/test62_out"
#!/bin/bash
mkdir -p files/original
/bin/echo '""'""'""""$USER""""'""'""' > "files/original/test63_out"
#!/bin/bash
mkdir -p files/original
/bin/echo $USER'$USER'text oui oui     oui  oui $USER oui      $USER '' > "files/original/test64_out"
#!/bin/bash
mkdir -p files/original
/bin/echo "text" "text$USER" ... "$USER" > "files/original/test65_out"
#!/bin/bash
mkdir -p files/original
/bin/echo > "files/original/test66_out"
#!/bin/bash
mkdir -p files/original
/bin/echo '' > "files/original/test67_out"
#!/bin/bash
mkdir -p files/original
/bin/echo '' > "files/original/test68_out"
#!/bin/bash
mkdir -p files/original
/bin/echo "" > "files/original/test69_out"
#!/bin/bash
mkdir -p files/original
/bin/echo '' "" > "files/original/test70_out"
#!/bin/bash
mkdir -p files/original
/bin/echo /bin/echo > "files/original/test71_out"
#!/bin/bash
mkdir -p files/original
/bin/echo test1 > "files/original/test72_out"
#!/bin/bash
mkdir -p files/original
/bin/echo 'test1' > "files/original/test73_out"
#!/bin/bash
mkdir -p files/original
/bin/echo "/bin/echo hallo" > "files/original/test74_out"
#!/bin/bash
mkdir -p files/original
/bin/echo /bin/echo"1" > "files/original/test75_out"
#!/bin/bash
mkdir -p files/original
/bin/echo "test1 test2" > "files/original/test76_out"
#!/bin/bash
mkdir -p files/original
/bin/echo "test1  test2" test3 > "files/original/test77_out"
#!/bin/bash
mkdir -p files/original
/bin/echo " test1 test2 " 'test3 ' > "files/original/test78_out"
#!/bin/bash
mkdir -p files/original
/bin/echo test1		test2 > "files/original/test79_out"
#!/bin/bash
mkdir -p files/original
/bin/echo $USER$TESTNOTFOUND$HOME$ > "files/original/test80_out"
#!/bin/bash
mkdir -p files/original
/bin/echo $USER$TESTNOTFOUND$HOME$WTF$PWD > "files/original/test81_out"
#!/bin/bash
mkdir -p files/original
/bin/echo -n test1 > "files/original/test82_out"
#!/bin/bash
mkdir -p files/original
/bin/echo -n "test1 test2" > "files/original/test83_out"
#!/bin/bash
mkdir -p files/original
/bin/echo -n "test1 test2" test3 > "files/original/test84_out"
#!/bin/bash
mkdir -p files/original
/bin/echo -n " test1 test2 " 'test3 ' > "files/original/test85_out"
#!/bin/bash
mkdir -p files/original
/bin/echo -n test1		test2 > "files/original/test86_out"
#!/bin/bash
mkdir -p files/original
/bin/echo test1 -n > "files/original/test87_out"
#!/bin/bash
mkdir -p files/original
/bin/echo "test1 -n"  > "files/original/test88_out"
#!/bin/bash
mkdir -p files/original
/bin/echo -n -n test1 > "files/original/test89_out"
#!/bin/bash
mkdir -p files/original
/bin/echo -n -n -n -n -n test1 > "files/original/test90_out"
#!/bin/bash
mkdir -p files/original
/bin/echo "  -nn " > "files/original/test91_out"
#!/bin/bash
mkdir -p files/original
/bin/echo "-n test1 -n test2" > "files/original/test92_out"
#!/bin/bash
mkdir -p files/original
/bin/echo "test1 -n test2" > "files/original/test93_out"
#!/bin/bash
mkdir -p files/original
/bin/echo ~42 > "files/original/test94_out"
#!/bin/bash
mkdir -p files/original
/bin/echo -n -n -nasd > "files/original/test95_out"
#!/bin/bash
mkdir -p files/original
/bin/echo -n -n -n-nnnnn > "files/original/test96_out"
#!/bin/bash
mkdir -p files/original
/bin/echo -n -nnnnnnn -n -nnn -nnnnn -n-n > "files/original/test97_out"
#!/bin/bash
mkdir -p files/original
/bin/echo -n -nnnnnnn -n -nnn -nnnnn -n feel my pain > "files/original/test98_out"
#!/bin/bash
mkdir -p files/original
/bin/echo -n -n -n-n > "files/original/test99_out"
#!/bin/bash
mkdir -p files/original
/bin/echo "'totally logical'" > "files/original/test100_out"
#!/bin/bash
mkdir -p files/original
/bin/echo 'totally logical' > "files/original/test101_out"
#!/bin/bash
mkdir -p files/original
/bin/echo ''totally logical'' > "files/original/test102_out"
#!/bin/bash
mkdir -p files/original
/bin/echo ""'totally logical'"" > "files/original/test103_out"
