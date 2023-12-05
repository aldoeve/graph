<?php
declare(strict_types=1);

function append_output($pipe,string &$output) {
        while (strlen($output)<80000 && strlen($data = fread($pipe, 8192)) > 0)
            $output .= $data;
}

// execute $cmd, limiting the time of execution to $limit
// stdin sent (possibly limited to size of pipe buffer, which is 64K)
// stdout and stderr captured and returned (up to 80K)
function execute(int $limit,string $cmd,string $stdin,&$stdout,&$stderr,?int $memlimit=512000):int {
    $descriptorspec = [
       0 => ["pipe", "r"],  // stdin
       1 => ["pipe", "w"],  // stdout
       2 => ["pipe", "w"],  // stderr
    ]; 

    // https://thirld.com/blog/2012/02/09/things-to-remember-when-using-ulimit/
    if ($memlimit)
        $cmd = "ulimit -Sv $memlimit; $cmd";
    $process = proc_open("ulimit -St $limit; $cmd",$descriptorspec,$pipes,getcwd());
    if (!is_resource($process))
        die("execution error: process could not be opened ($cmd)");  

    fwrite($pipes[0], $stdin);
    fclose($pipes[0]);

    stream_set_blocking($pipes[1], false);
    stream_set_blocking($pipes[2], false);

    $status = proc_get_status($process);
    $pid = $status['pid'];
    posix_setpgid($pid,0); // create a new process group

    $stdout = '';
    $stderr = '';
    $start = time();
    while (!feof($pipes[1]) || !feof($pipes[2])) {
        append_output($pipes[1],$stdout);
        append_output($pipes[2],$stderr);
        if (strlen($stdout) > 80000
        ||  strlen($stderr) > 80000
        ||  time()-$start > $limit+2) {
            posix_kill(-$pid,SIGKILL); // kill the process group
            append_output($pipes[1],$stdout);
            append_output($pipes[2],$stderr);
            if (strlen($stdout) > 80000 || strlen($stderr) > 80000) $stderr = "too much output generated\n".$stderr;
            $stderr = "Killed\n".$stderr; // to match bash(?, or OOMK?) message
            break;
        }
        // wait 3 seconds or until data is available
        $read_streams = [$pipes[1],$pipes[2]];
        $write_streams = [];
        $except_streams = [];
        stream_select($read_streams,$write_streams,$except_streams,3,0);
    }

    fclose($pipes[2]);
    fclose($pipes[1]);

    $stat = file_get_contents("/proc/$pid/stat");
    $stat = explode(" ",$stat,18);
    proc_close($process);
    
    return (int)$stat[15];
}
