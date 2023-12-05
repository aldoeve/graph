<?php

// generate a random starting graph

if (count($argv) != 3)
    die("usage: php generate.php <V> <E>");

$V = $argv[1];
$E = $argv[2];

$edges = [];
for ($i=2; $i<=$V; $i++)
    for ($j=1; $j<$i; $j++)
        $edges[] = "$i $j ".mt_rand(1,100);
shuffle($edges);

echo "$V\n0\n$E\n";
for ($i=0; $i<$E; $i++)
    echo $edges[$i]."\n";
