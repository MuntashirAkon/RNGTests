<?php
    define('EACH_COUNT', 100);
    define('C_CRUSH', 15);
    define('C_RABBIT', 51);
    define('C_ALPHABIT', 33);
    if($argc != 2){
        echo "USAGE: analyze_testu01 testu01_output.txt\n";
        exit(1);
    }
    //echo "IQM: ". iqm([5, 8, 4, 38, 8, 6, 9, 7, 7, 3, 1, 6]) ."\n";
    $data = [];
    // Check for UTF-16
    system('find "'.$argv[1].'" -exec file "{}" ";" | grep UTF-16 > /dev/null', $return);
    if($return == 0){
        $grep = 'iconv -f utf-16 -t utf-8 "'.$argv[1].'" | grep "p-value of test"';
    } else {
        $grep = 'grep "p-value of test" "'.$argv[1].'"';
    }
    exec($grep.' | sed -e \'s/p-value of test *: *\(1 -  \)*//\' -e \'s/\s*\*\*\*\*\*//\'', $data);
    // SMALLCRUSH
    $crush_first = 0;
    $crush_last = $crush_first + EACH_COUNT * C_CRUSH;
    analyze(C_CRUSH, $crush_first, $crush_last, 'smallcrush');
    // RABBIT
    $rabbit_first = $crush_last;
    $rabbit_last = $rabbit_first + EACH_COUNT * C_RABBIT;
    analyze(C_RABBIT, $rabbit_first, $rabbit_last, 'rabbit');
    // ALPHABIT
    $alphabit_first = 0;
    $alphabit_last = $alphabit_first + EACH_COUNT * C_ALPHABIT;
    analyze(C_ALPHABIT, $alphabit_first, $alphabit_last, 'alphabit');
    
    exit(0);

    function analyze($n, $i_start, $i_end, $out_file){ // i_end is exclusive
        global $data;
        $i = $i_start;
        $result_mat = [];
        $output = '';
        for($j = 0; $j < $n; ++$j) $result_mat[$j] = [];
        for($j = 0; $i < $i_end; ++$i, ++$j){
            array_push($result_mat[$j], (float)$data[$i]);
            $output .= $data[$i];
            if($j == ($n - 1)){
                $j = -1;
                $output .= "\n";
            } else {
                $output .= ",";
            }
        }
        file_put_contents("./{$out_file}.csv", $output);
        $output = "#,IQM,AVG\n";
        for($j = 0; $j < $n; ++$j){
            $output .= ($j + 1) . ',' . iqm($result_mat[$j]) . ',' . (array_sum($result_mat[$j])/count($result_mat[$j])) . "\n";
        }
        file_put_contents("./{$out_file}_res.csv", $output);
    }

    function iqm($arr){
        sort($arr);
        $n = count($arr);
        $x = 0;
        for($i = $n/4; $i< 3*$n/4; ++$i){
            $x += $arr[$i];
        }
        $x *=2/$n;
        return $x;
    }
