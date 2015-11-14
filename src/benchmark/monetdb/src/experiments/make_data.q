opts:.Q.opt .z.x;
if[not `size in key opts; show "Usage: q make_data.q -size #"];
n:"I"$first opts`size;
v1:n?0Wi;
v2:n?0Wi;
v:v1 - v2; // max:maxInt - 0, min:0 - maxInt
random_numbers:([]val:v);
save `:tables/random_numbers
`:tables/random_numbers.txt 0:string v
exit 0




