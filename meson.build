project(
    '42sh',
    'c',
    version: '0.1',
    license: 'MIT',
    default_options: [
        'c_std=c99',
        'warning_level=3',
        'default_library=static',

        # these options would not be suitable in a
        # production configuration, but development easier
        'b_sanitize=address',
        'buildtype=debug',
        'werror=true',
    ],
)


# print a summary of the build configuration before each build starts
summary({
    'optimization': get_option('optimization'),
    'debug': get_option('debug'),
    'b_sanitize': get_option('b_sanitize'),
    'warning_level': get_option('warning_level'),
    'werror': get_option('werror'),
})


# add some project-wide flags
cflags = ['-D_POSIX_SOURCE', '-D_POSIX_C_SOURCE=200809L']
add_project_arguments(cflags, language: 'c')


# interpret the meson.build in this directory
all_sources = ['src/42sh.c', 'src/eval_ast/cd_command.c', 'src/eval_ast/eval_operators.c', 'src/eval_ast/eval_redirection.c',
'src/eval_ast/eval_for.c', 'src/eval_ast/eval_pipe.c', 'src/eval_ast/eval_until.c',
'src/eval_ast/exec_other_command.c', 'src/ast/ast.c', 'src/eval_ast/echo_command.c',
'src/eval_ast/eval_ast.c', 'src/eval_ast/eval_negation.c', 'src/eval_ast/eval_while.c',
'src/lexer/lexer.c', 'src/lexer/list_lexer.c', 'src/lexer/memory.c', 'src/lexer/token_lexer.c',
'src/parser/parser.c', 'src/parser/parser_and_or.c', 'src/parser/parser_compound_list.c',
'src/parser/parser_do_group.c', 'src/parser/parser_element.c', 'src/parser/parser_else_clause.c',
'src/parser/parser_input.c', 'src/parser/parser_list.c', 'src/parser/parser_rule_if.c',
'src/parser/parser_separator.c', 'src/parser/parser_shell_command.c', 'src/parser/parser_simple_command.c',
'src/parser/parser_case_clause.c', 'src/parser/parser_case_item.c', 'src/parser/parser_command.c', 
'src/parser/parser_element.c', 'src/parser/parser_funcdec.c', 'src/parser/parser_pipeline.c', 'src/parser/parser_prefix.c',
'src/parser/parser_redirection.c', 'src/parser/parser_rule_case.c', 'src/parser/parser_rule_for.c', 'src/parser/parser_rule_while.c',
'src/parser/parser_separator.c', 'src/parser/parser_rule_until.c', 'src/pretty_print/prettyprint.c','src/hash_map/dump.c', 'src/hash_map/hash_map.c', 'src/hash_map/hash.c']
subdir('src')


# find readline, which some of the modules below link with
cc = meson.get_compiler('c')
readline_dep = cc.find_library('readline', required: true)


bin = executable(
    '42sh',
    all_sources,
    include_directories: 'src',
    install: true,
    dependencies: [readline_dep],
)


run_tests = meson.source_root() / 'tests/run_tests'
custom_target(
    'check',
    command: [run_tests, bin] + get_option('check_args'),
    # give the testsuite exclusive access to the terminal, which enables
    # pretty colors and live testsuite results (meson buffers it all otherwise)
    console: true,
    # eventhough this rule output no file, we have to the output file of the rule is mandatory, but as
    # but it doesn't matter as the rule is always built
    output: 'check',
    build_always_stale: true,
    # if this option is enabled, tests will run for all builds
    build_by_default: get_option('force_check'),
)

if get_option('doc')
    subdir('doc')
endif
