# Test 1: Simple pipe
"test1_simple" "< f_infile grep .c wc -w > f_outfile2"

# Test 2: No outfile specified
"test2_no_outfile" "< f_infile grep | -v .c cat > f_outfile2"

# Test 3: Wrong command, error expected
"test3_wrong_command" "< f_infile greep -v .c wrong > f_outfile2"

# Test 4: Wrong permission, error expected
"test4_wrong_permission" "< f_infile ls grep .c wc > f_outfile2"

# Test 5: ./ls, error expected
"test5_ls_error" "< f_infile ./ls wc -w ls > f_outfile2"

# Test 6: Multi pipes simple
"test6_multi_pipes_simple" "< f_infile grep . grep .c wc -w > f_outfile2"

# Test 7: Hakin 1, 3 errors expected
"test7_hakin1" "< f_infile jdgsfhdsg shdusah udhubsa /bin/ls > f_outfile2"

# Test 8: Hakin 2, 3 errors expected
"test8_hakin2" "< f_infile cat /dev/urandom head -1 > f_outfile2"

# Test 9: Wrong permission outfile, error expected
"test9_wrong_permission_outfile" "< f_infile /bin/ls /bin/cat /bin/cat /bin/cat > f_outfile2"

# Test 10: Extra errors expected
"test10_extra_errors" "< f_infile jdgsfhdsg shdusah udhubsa /bin/ls > f_outfile2"
