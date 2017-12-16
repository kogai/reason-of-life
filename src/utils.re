let rec range = (n) =>
  switch n {
  | 0 => []
  | n => [n, ...range(n - 1)]
  };
