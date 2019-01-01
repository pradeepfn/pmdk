#!/usr/bin/env python

import argparse
import sys
import os
import shutil
DBG=1

#config
__home = os.getcwd()
__tmlib_home = '/home/pradeep/nvmtsx/tmlib'

__ctree = 'ctree'
__empty = ''

workload_l = []
workload_l.append(__ctree)

__seq       = 'seq'
__tsxseq    = 'tsxseq'
__undo      = 'undo'

logtype_l = []
logtype_l.append(__seq)
logtype_l.append(__tsxseq)
logtype_l.append(__undo)

parser = argparse.ArgumentParser(prog="runscript", description="script to run pmdk runscript")
parser.add_argument('-b', dest='build', action='store_true', default=False, help="build benchmark")
parser.add_argument('-c', dest='clean', action='store_true', default=False, help="clean benchmark")
parser.add_argument('-r', dest='run', action='store_true', default=False, help="run benchmark")
parser.add_argument('-w', dest='workload', default=__empty , help='workload name, eg: ctree, hashmap', choices=workload_l)
parser.add_argument('-lt', dest='logtype', default=__empty , help='logging type', choices=logtype_l)
try:
    args = parser.parse_args()

except:
    sys.exit(0)

def dbg(s):
    if DBG==1:
        print s

def msg(s):
    print '\n' + '>>>' +s + '\n'



def cd(dirt):

    dbg(dirt)


    if dirt == __home:
        os.chdir(__home);
    else:

        path = __home + '/' + dirt
        dbg(path)

        try:
            os.chdir(path)
        except:
            print 'invalid directory ', path
            sys.exit(0)

def sh(cmd):

    msg(cmd)
    try:
        os.system(cmd)
    except:
        print 'invalid cmd', cmd
        sys.exit(0)


def libname(lt):
    if lt == __tsxseq:
        return __tsxseq
    else:
        return None


#build nvmtsx with requested logging scheme found in
# tmlib. we have to include proper headers
def build_libpmemnvmtsx():
    ltype = args.logtype

    lib_h = 'src/libpmemnvmtsx'
    cd(lib_h)
    cmd = 'make TMBUILD='+  ltype + ' TMLIBDIR=' + __tmlib_home
    sh(cmd)
    cd(__home)

def build_ctree():
    ltype = args.logtype

    map_h = 'src/examples/libpmemobj'
    #build c-tree first
    cd(map_h + '/tree_map')
    cmd = 'make TMBUILD='+  ltype + ' TMLIBDIR=' + __tmlib_home
    sh(cmd)
    cd(__home)
    cd(map_h + '/map')
    cmd = 'make TMBUILD='+  ltype + ' TMLIBDIR=' + __tmlib_home
    sh(cmd)
    cd(__home)


    #build map that wraps c-tree
    cd(__home)

def build_bench():
    ltype = args.logtype
    __tmlib_path = ''
    bench_h = 'src/benchmarks'
    cd(bench_h)
    if libname(ltype) is not None:
        __tmlib_path = __tmlib_home + '/build/lib' + ltype + '.a'
    cmd = 'make TMBUILD='+  ltype + ' TMLIBDIR=' + __tmlib_home +\
          ' TMLIBPATH=' + __tmlib_path
    sh(cmd)
    cd(__home)


def clean():
    lib_h = 'src/libpmemnvmtsx'
    cd(lib_h)
    cmd = 'make clean'
    sh(cmd)
    cd(__home)

    map_h = 'src/examples/libpmemobj'
    cd(map_h + '/tree_map')
    cmd = 'make clean'
    sh(cmd)
    cd(__home)
    cd(map_h + '/map')
    cmd = 'make clean'
    sh(cmd)
    cd(__home)

    bench_h = 'src/benchmarks'
    cd(bench_h)
    cmd = 'make clean'
    sh(cmd)
    cd(__home)


def run_bench():
    cmd = "./run_ctree.sh --small"
    sh(cmd)




if __name__ == '__main__':

    b = args.build
    c = args.clean

    if args.build is True:
        build_libpmemnvmtsx()
        build_ctree()
        build_bench()
    if args.clean is True:
        clean()
    if args.run is True:
        run_bench()