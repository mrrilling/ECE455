# include < iostream >
# include < vector >
# include < thread >
# include < numeric >
# include < random >
# include < chrono >
void partial_sum ( const std :: vector < int > & data ,
size_t start , size_t end , long long & out ) {
out = std :: accumulate ( data . begin () + start , data . begin () + end , 0 LL ) ;
}
int main () {
const size_t N = 1 0 0 0 0 0 0 0 ;
const int T = std :: thread :: hardware_concurrency () ?
std :: thread :: hardware_concurrency () : 4 ;
std :: vector < int > data ( N ) ;
std :: mt 1 9 9 3 7 rng ( 4 2 ) ;
std :: uniform_int_distribution < int > dist ( 1 , 1 0 0 ) ;
for ( auto & x : data ) x = dist ( rng ) ;
// Baseline ( single - threaded )
auto t 0 = std :: chrono :: high_resolution_clock :: now () ;
long long baseline = std :: accumulate ( data . begin () , data . end () , 0 LL ) ;
auto t 1 = std :: chrono :: high_resolution_clock :: now () ;
// Parallel
std :: vector < long long > partials (T , 0 ) ;
std :: vector < std :: thread > threads ;
threads . reserve ( T ) ;
size_t chunk = N / T ;
auto p 0 = std :: chrono :: high_resolution_clock :: now () ;
for ( int i = 0 ; i < T ; ++ i ) {
size_t s = i * chunk ;
size_t e = ( i == T - 1 ) ? N : s + chunk ;
threads . emplace_back ( partial_sum , std :: cref ( data ) , s , e , std :: ref (
partials [ i ]) ) ;
}
for ( auto & th : threads ) th . join () ;
long long total = std :: accumulate ( partials . begin () , partials . end () , 0 LL )
;
auto p 1 = std :: chrono :: high_resolution_clock :: now () ;
std :: chrono :: duration < double > t_base = t 1 - t 0 ;
std :: chrono :: duration < double > t_par = p 1 - p 0 ;
std :: cout << " Baseline sum : " << baseline
<< " Time : " << t_base . count () << " s \ n " ;
std :: cout << " Parallel sum : " << total
<< " Time : " << t_par . count () << " s \ n " ;
return 0 ;
}