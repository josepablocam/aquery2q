echo "generating unoptimized AST viz"
../a2q -p progress_report_examples.a | dot -Tpdf -o generated.pdf
echo "generated optimized AST viz"
../a2q -p -a 1 progress_report_examples.a | dot -Tpdf -o generated_optimized.pdf
echo "generating unoptimized code"
../a2q -c progress_report_examples.a > generated.q
echo "generating optimized code"
../a2q -c -a 1 progress_report_examples.a > generated_optimized.q
