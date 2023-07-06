#include "unit_tests.h"
#include "hw6.h"

TestSuite(student_invalid_args, .timeout=TEST_TIMEOUT);
TestSuite(student_output, .timeout=TEST_TIMEOUT);
static char args[ARGS_TEXT_LEN];

Test(student_invalid_args, args_missing02, .description="-s option is missing.") {
    char *test_name = "args_missing02";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s -r end %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, MISSING_ARGUMENT);
}
Test(student_invalid_args, args_missing03, .description="-s option is missing.") {
    char *test_name = "args_missing03";
    prep_files("unix.txt", test_name);    
    sprintf(args, "%s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, MISSING_ARGUMENT);
}

Test(student_invalid_args, duplicate_argument02, .description="-s option is missing.") {
    char *test_name = "duplicate_argument02";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s stay -r end -r -l 10,15 -w %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, DUPLICATE_ARGUMENT);
}
Test(student_invalid_args, duplicate_argument03, .description="-s option is missing.") {
    char *test_name = "duplicate_argument03";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s -r end -l -h -h -s the 10,15 -w %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, DUPLICATE_ARGUMENT);
}
Test(student_invalid_args, duplicate_argument04, .description="-s option is missing.") {
    char *test_name = "duplicate_argument04";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-r -l -s end -l 10,15 -l -w %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, DUPLICATE_ARGUMENT);
}

Test(student_invalid_args, input_file_missing02, .description="Input file is missing.") {
    char *test_name = "input_file_missing";
    sprintf(args, "-s the -r end -l 9,10 %s/%s.out.txt", TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, INPUT_FILE_MISSING);
}

Test(student_invalid_args, s_argument_missing04, .description="-s option is missing.") {
    char *test_name = "s_argument_missing04";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s -r end -l 10,15 -w doowap %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, S_ARGUMENT_MISSING);
}
Test(student_invalid_args, s_argument_missing05, .description="-s option is missing.") {
    char *test_name = "s_argument_missing05";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s -l 10,15 -w %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, S_ARGUMENT_MISSING);
}
Test(student_invalid_args, s_argument_missing06, .description="-s option is missing.") {
    char *test_name = "s_argument_missing06";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-r die -l -s -w %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, S_ARGUMENT_MISSING);
}

Test(student_invalid_args, r_argument_missing04, .description="-s option is missing.") {
    char *test_name = "r_argument_missing04";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s that -r -l 10,15 -w %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, R_ARGUMENT_MISSING);
}
Test(student_invalid_args, r_argument_missing05, .description="-s option is missing.") {
    char *test_name = "r_argument_missing05";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-l 8 -s 10,15 -w %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, R_ARGUMENT_MISSING);
}
Test(student_invalid_args, r_argument_missing06, .description="-s option is missing.") {
    char *test_name = "r_argument_missing06";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s end -l 10,15 -w %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, R_ARGUMENT_MISSING);
}

Test(student_invalid_args, l_argument_missing04, .description="-s option is missing.") {
    char *test_name = "l_argument_missing04";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s that -r true -l %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, L_ARGUMENT_INVALID);
}
Test(student_invalid_args, l_argument_missing05, .description="-s option is missing.") {
    char *test_name = "l_argument_missing05";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-l -10,20 -s hi -r bye %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, L_ARGUMENT_INVALID);
}
Test(student_invalid_args, l_argument_missing06, .description="-s option is missing.") {
    char *test_name = "l_argument_missing06";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s start -l ,15 -r nope %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, L_ARGUMENT_INVALID);
}

Test(student_invalid_args, wildcard_invalid03, .description="Search text is not properly formatted.") {
    char *test_name = "wildcard_invalid03";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s *h* -r HELLO -w %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, WILDCARD_INVALID);
}
Test(student_invalid_args, wildcard_invalid04, .description="Search text is not properly formatted.") {
    char *test_name = "wildcard_invalid04";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s h -r HELLO -w %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, WILDCARD_INVALID);
}
Test(student_invalid_args, wildcard_invalid05, .description="Search text is not properly formatted.") {
    char *test_name = "wildcard_invalid05";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s *hello** -r HELLO -w BOO %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    int status = run_using_system_no_valgrind(test_name, args);
    expect_error_exit(status, WILDCARD_INVALID);
}

Test(student_output, simple_search011, .description="Perform a simple replacement over entire file. Input text contains a single word.") {
    char *test_name = "simple_search011";
    prep_files("punctuation.txt", test_name);    
    sprintf(args, "-s code -r homework -l 1,1 %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    run_using_system_no_valgrind(test_name, args);
    expect_outfile_matches(test_name);
}
Test(student_output, simple_search012, .description="Perform a simple replacement over entire file. Input text contains a single word.") {
    char *test_name = "simple_search012";
    prep_files("punctuation.txt", test_name);    
    sprintf(args, "-s So -r Thus %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    run_using_system_no_valgrind(test_name, args);
    expect_outfile_matches(test_name);
}
Test(student_output, simple_search013, .description="Perform a simple replacement over entire file. Input text contains a single word.") {
    char *test_name = "simple_search013";
    prep_files("turing.txt", test_name);    
    sprintf(args, "-l 10ghyt,26jfh -s a -r BBB %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    run_using_system_no_valgrind(test_name, args);
    expect_outfile_matches(test_name);
}
Test(student_output, simple_search014, .description="Perform a simple replacement over entire file. Input text contains a single word.") {
    char *test_name = "simple_search014";
    prep_files("turing.txt", test_name);    
    sprintf(args, "-s . -r ! %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    run_using_system_no_valgrind(test_name, args);
    expect_outfile_matches(test_name);
}
Test(student_output, simple_search015, .description="Perform a simple replacement over entire file. Input text contains a single word.") {
    char *test_name = "simple_search015";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s ix -r ux %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    run_using_system_no_valgrind(test_name, args);
    expect_outfile_matches(test_name);
}
Test(student_output, simple_search016, .description="Perform a simple replacement over entire file. Input text contains a single word.") {
    char *test_name = "simple_search016";
    prep_files("unix.txt", test_name);
    sprintf(args, "-s 19 -l 8,40 -r 20 %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    run_using_system_no_valgrind(test_name, args);
    expect_outfile_matches(test_name);
}
Test(student_output, simple_search017, .description="Perform a simple replacement over entire file. Input text contains a single word.") {
    char *test_name = "simple_search017";
    prep_files("oneword.txt", test_name);    
    sprintf(args, "-s Home -r School %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    run_using_system_no_valgrind(test_name, args);
    expect_outfile_matches(test_name);
}

Test(student_output, wildcard_search25, .description="Perform a wildcard replacement over entire file. Input text contains a single word.") {
    char *test_name = "wildcard_search25";
    prep_files("punctuation.txt", test_name);    
    sprintf(args, "-s *code -r homework -l 1,1 -w %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    run_using_system_no_valgrind(test_name, args);
    expect_outfile_matches(test_name);
}
Test(student_output, wildcard_search26, .description="Perform a wildcard replacement over entire file. Input text contains a single word.") {
    char *test_name = "wildcard_search26";
    prep_files("punctuation.txt", test_name);    
    sprintf(args, "-w -s S* -r Thus %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    run_using_system_no_valgrind(test_name, args);
    expect_outfile_matches(test_name);
}
Test(student_output, wildcard_search27, .description="Perform a wildcard replacement over entire file. Input text contains a single word.") {
    char *test_name = "wildcard_search27";
    prep_files("turing.txt", test_name);    
    sprintf(args, "-l 10ghyt,26jfh -w -s a* -r BBB %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    run_using_system_no_valgrind(test_name, args);
    expect_outfile_matches(test_name);
}
Test(student_output, wildcard_search28, .description="Perform a wildcard replacement over entire file. Input text contains a single word.") {
    char *test_name = "wildcard_search28";
    prep_files("turing.txt", test_name);    
    sprintf(args, "-s *rn -w -r ! %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    run_using_system_no_valgrind(test_name, args);
    expect_outfile_matches(test_name);
}
Test(student_output, wildcard_search29, .description="Perform a wildcard replacement over entire file. Input text contains a single word.") {
    char *test_name = "wildcard_search29";
    prep_files("unix.txt", test_name);    
    sprintf(args, "-s ix* -r ux -w %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    run_using_system_no_valgrind(test_name, args);
    expect_outfile_matches(test_name);
}
Test(student_output, wildcard_search30, .description="Perform a wildcard replacement over entire file. Input text contains a single word.") {
    char *test_name = "wildcard_search30";
    prep_files("unix.txt", test_name);
    sprintf(args, "-s 19* -l 8,40 -r 20 -w %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    run_using_system_no_valgrind(test_name, args);
    expect_outfile_matches(test_name);
}
Test(student_output, wildcard_search31, .description="Perform a wildcard replacement over entire file. Input text contains a single word.") {
    char *test_name = "wildcard_search31";
    prep_files("oneword.txt", test_name);    
    sprintf(args, "-s Home* -r School -w %s/%s.in.txt %s/%s.out.txt", TEST_INPUT_DIR, test_name, TEST_OUTPUT_DIR, test_name);
    run_using_system_no_valgrind(test_name, args);
    expect_outfile_matches(test_name);
}
