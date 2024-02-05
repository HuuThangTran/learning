long long array_total(long long* a, long long n) {
long long total = 0;
for (long long i=0; i<n; i++) {
total += a[i];
}
return total;
}