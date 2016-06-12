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


    def consume_markers(self, acc, line):
        """
        Consume special markers such as parenthesis, braces, and verbatim-q
        wrappers in order to allow empty lines in between such markers
        without triggering compilation
        """
        special = {'(' : ')', '{' : '}', '[' : ']'}
        keys = special.keys()
        vals = special.values()
        # characters that we should be checking for opening/closing markers
        char_check = keys + vals
        # we use '[]' to represent <q></q> for simplicity of matching
        clean_line = line.replace('<q>', '[').replace('</q>', ']')
        relevant = [c for c in clean_line if c in char_check]

        for c in relevant:
            if c in keys:
                acc.append(c)
            elif not acc:
                # no marker available that needs closing
                clean_c = '</q>' if c == ']' else c
                raise ValueError("Unopened " + clean_c)
            else:
                latest = acc[-1]
                if c != special[latest]:
                    clean_latest = '<q>' if latest == '[' else latest
                    raise ValueError("Mismatched " + clean_latest)
                else:
                    acc.pop()



    def main(self):
        """ REPL """
        cmd = ""
        # contains (), {}, <q></q> that are yet to be matched
        markers = []
        while True:
            try:
                line = raw_input(">")
                # we accept empty lines within markers
                # without executing
                if not line and not markers:
                    compiled = self.compile(cmd)
                    results = self.run_cmd(compiled, self.FUN_NAME)
                    self.display(results)
                    compiled.close()
                    cmd = ""
                else:
                    # only concatenate if not a comment
                    # and non-empty line
                    if line.lstrip()[:2] != '//' and line:
                        cmd += " " + line
                        # match any necessary markers
                        self.consume_markers(markers, line)
            except ValueError, err:
                print "Error: " + err.message
                # flush command and markers
                cmd = ""
                markers = []
            except EOFError:
                # CTRL+D terminates the loop and exits interpreter, so cleanup
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
