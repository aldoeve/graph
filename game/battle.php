<?php
// run a battle between two algorithms

function read_graph(string $filename):array {
    $input = file_get_contents($filename);
    $input = preg_replace("/\\s+/"," ",$input);
    $input = explode(" ",$input);

    $V = array_shift($input);

    $pe = [];
    $P = array_shift($input);
    for ($i=0; $i<$P; $i++) {
        $s = array_shift($input);
        $d = array_shift($input);
        $c = array_shift($input);
        $pe[] = [$s,$d,$c];
    }

    $ue = [];
    $U = array_shift($input);
    for ($i=0; $i<$U; $i++) {
        $s = array_shift($input);
        $d = array_shift($input);
        $c = array_shift($input);
        $ue[] = [$s,$d,$c];
    }
    return [$pe,$ue,$V];
}

function total_cost(array $pe,array $ue,int $V):int {
    $M = 999999999;
    $G = array_fill(1,$V,array_fill(1,$V,$M));
    foreach ($pe as $e)
        $G[$e[0]][$e[1]] = $e[2];
    foreach ($pe as $e)
        $G[$e[1]][$e[0]] = $e[2];
    foreach ($ue as $e)
        $G[$e[0]][$e[1]] = $e[2];
    foreach ($ue as $e)
        $G[$e[1]][$e[0]] = $e[2];

    for ($k=1; $k<=$V; $k++)
        for ($i=1; $i<=$V; $i++)
            for ($j=1; $j<=$V; $j++)
                if ($G[$i][$k] + $G[$k][$j] < $G[$i][$j])
                    $G[$i][$j] = $G[$i][$k] + $G[$k][$j];

    $total = 0;
    for ($i=1; $i<=$V; $i++)
        for ($j=1; $j<=$V; $j++)
            $total += $G[$i][$j];
    return $total;
}

function to_string(array $pe,array $ue,int $V):string {
    return "$V\n"
        .count($pe)."\n".implode("",array_map(fn($d)=>"$d[0] $d[1] $d[2]\n",$pe))
        .count($ue)."\n".implode("",array_map(fn($d)=>"$d[0] $d[1] $d[2]\n",$ue));
}

require_once("execute.php");

if (count($argv) != 4)
    die("usage: php battle.php <p1> <p2> <testfile.txt>\n");

[$pe,$ue,$V] = read_graph($argv[3]);

while (true) {
    $total = total_cost($pe,$ue,$V);
    if ($total > 1000000) die("graph is unconnected\n");
    echo "total cost is $total\n";

    if (count($ue) == 0)
        die("no more unprotected edges\n");

    // cut
    $stdout = $stderr = "";
    //echo to_string($pe,$ue,$V);
    $ticks = execute(30,"./$argv[1] cut",to_string($pe,$ue,$V),$stdout,$stderr);
    $which = (int)$stdout;
    if ($which < 0 || $which >= count($ue)) 
        die("$argv[1] returned $which, but only ".count($ue)." unprotected edges\n");

    echo "$ticks ticks for $argv[1] to cut $which: {$ue[$which][0]} {$ue[$which][1]} {$ue[$which][2]}, new ";
    unset($ue[$which]);
    $ue = array_values($ue);
    //echo implode(";",array_map(fn($d)=>"$d[0] $d[1] $d[2]",$ue))."\n";

    $total = total_cost($pe,$ue,$V);
    if ($total > 1000000) die("graph is unconnected\n");
    echo "total cost is $total\n";

    if (count($ue) == 0)
        die("no more unprotected edges\n");

    // short
    $stdout = $stderr = "";
    $ticks = execute(30,"./$argv[2] short",to_string($pe,$ue,$V),$stdout,$stderr);
    $which = (int)$stdout;
    if ($which < 0 || $which >= count($ue)) 
        die("$argv[2] returned $which, but only ".count($ue)." unprotected edges\n");
    echo "$ticks ticks for $argv[2] to short $which: {$ue[$which][0]} {$ue[$which][1]} {$ue[$which][2]}, new ";
    $pe[] = $ue[$which];
    unset($ue[$which]);
    $ue = array_values($ue);
}
