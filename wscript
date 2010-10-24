APPNAME = 'curl_tut'
VERSION = '0.0.1'

srcdir = '.'
blddir = 'build'

def set_options(opt):
    opt.tool_options('compiler_cc')
    # プロジェクトのオプションを設定する
    # 最初に呼ばれる
    pass

def configure(conf):
    conf.check_tool('compiler_cc')
    # ライブラリのチェックなど
    # waf configure 時に呼ばれる
    pass

def build(bld):
    bld(features = 'c cprogram',
        source = 'src/curl_tut.c',
        target = 'curl_tut',
        lib = ['curl'])
    # ビルドの情報を書く
    # waf build 時に呼ばれる
    pass

def shutdown(ctx):
    # 終了時に何かをさせたいとき
    # 最後に呼ばれる
    pass
