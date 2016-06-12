# Simple aquery "interpreter"
# Takes aquery in stdin, writes to temporary file, compiles into q
# and uses Matt Warren's qPy for communication with q


import subprocess
import tempfile
import kdb
import os
import readline
from sys import argv

class a2qinterpreter:
    def __init__(self, host, port, user):
        self.host = host
        self.port = port
        self.user = user
        self.q = self.init_q()
        # hackish but the unfortunate nature of things for now
        self.FUN_NAME = ".aq.q0"
        self.COMPILED_NAME = "_compiled.q"

    def init_q(self):
        """ Initialize connection q server """
        return kdb.q(self.host, self.port, self.user)

    def clear_console(self):
        """ Clear console colors after any error messages """
        print "\033[0m"

    def compile(self, aquery):
        """ Compiles aquery to q by using temporary files """
        in_file = tempfile.NamedTemporaryFile()
        in_file.write(aquery)
        in_file.flush()

        out_file = open(self.COMPILED_NAME, "w+")
        # define dummy function in case command doesn't create function
        out_file.write(self.FUN_NAME + ":{}; ")
        out_file.close()

        inter_file = tempfile.NamedTemporaryFile()

        aquery_compiler = ['a2q', '-a', '1', '-c', '-s', '-o']
        try:
            ret = subprocess.check_output(aquery_compiler + [inter_file.name, in_file.name])
            out_file = open(self.COMPILED_NAME, "a")
            out_file.write(inter_file.read())
            out_file.flush()
        except subprocess.CalledProcessError, err:
            print "Error: " + err.output
            # make sure we clear out any coloring
            self.clear_console()
        except OSError, err:
            print "Make sure a2q executable is in your path"
            print err.strerror
        finally:
            in_file.close()
            inter_file.close()
            return out_file


    def run_cmd(self, in_file, fun_name):
        """ Run aquery in q by submitting file name to load and calling function wrapper """
        load_cmd = 'system "l '  + in_file.name + '"'
        # run aquery function
        run_cmd = fun_name + "[]"
        # format for display
        print_cmd = ".Q.s"
        try:
            # load new aquery function definition
            self.q.k(load_cmd)
            # actually run and return stringified results
            return self.q.k(print_cmd + " " + run_cmd)
        except Exception, err:
            print "Error: " + err.message
            self.clear_console()
            return ""


    def display(self, s):
        """ Displays q stringified results in python """
        print "".join(s)

    def usage(self):
        msg = """
        Usage: python a2qinterpret.py [host port user]
        Defaults to host: localhost, port: 7089, user: ""
        if none provided
        """
        print msg


    def main(self):
        """ REPL """
        cmd = ""
        while True:
            try:
                line = raw_input(">")
                if not line:
                    compiled = self.compile(cmd)
                    results = self.run_cmd(compiled, self.FUN_NAME)
                    self.display(results)
                    compiled.close()
                    cmd = ""
                else:
                    # only concatenate if not a comment
                    if line.lstrip()[:2] != '//':
                        cmd += " " + line
            except EOFError:
                os.path.exists(self.COMPILED_NAME) and os.remove(self.COMPILED_NAME)
                exit(0)


if __name__ == "__main__":
    if len(argv) > 1 and (argv[1] == "--help" or argv[1] == "-h"):
        usage()
        exit(0)
    if len(argv) == 4:
        host = argv[1]
        port = int(argv[2])
        user = argv[3]
    else:
        host = "localhost"
        port = 7089
        user = ""
    # take in options
    interp = a2qinterpreter(host, port, user)
    interp.main()
