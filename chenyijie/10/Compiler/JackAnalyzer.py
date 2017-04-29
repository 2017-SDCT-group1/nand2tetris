import CompilationEngine as CE
import os
file_local = [x for x in os.listdir('.') if os.path.isfile(x)]

def main():
    for filename in file_local:
        if filename.split('.', 2)[1]=='jack':
            print('正在编译%s' % filename)
            CompilerEngine = CE.CompilationEngine(filename)
if __name__ == '__main__':
    main()