#! /usr/bin/env python2

import glob
import os.path


def options(opt):
    pass

def configure(cfg):
    pass

def build(bld):
    bld.shlib(
        source = '''
            src/action_play_mur.cc
            src/action_play_nose.cc
            src/api.cc
            src/entry.cc
            src/game_state.cc
            src/interface.cc
            src/rules.cc
        ''',
        defines = ['MODULE_COLOR=ANSI_COL_BROWN', 'MODULE_NAME="rules"'],
        target = 'thjx2017',
        use = ['stechec2'],
    )

    abs_pattern = os.path.join(bld.path.abspath(), 'src/tests/test-*.cc')
    for test_src in glob.glob(abs_pattern):

        test_name = os.path.split(test_src)[-1]
        test_name = test_name[5:-3]

        # Waf requires a relative path for the source
        src_relpath = os.path.relpath(test_src, bld.path.abspath())

        bld.program(
            features = 'gtest',
            source = src_relpath,
            target = 'thjx2017-test-{}'.format(test_name),
            use = ['thjx2017', 'stechec2-utils'],
            includes = ['.'],
            defines = ['MODULE_COLOR=ANSI_COL_PURPLE',
                       'MODULE_NAME="thjx2017"'],
        )

    bld.install_files('${PREFIX}/share/stechec2/thjx2017', [
        'thjx2017.yml',
    ])
