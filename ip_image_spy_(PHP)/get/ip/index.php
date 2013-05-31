<?php
	function cmp_filetime($a, $b){ 
    		return filemtime($a)>filemtime($b)?-1:1; 
	}

	$dir_h = opendir(".");
	while($file = readdir($dir_h)){
		if($file=="." || $file==".." || $file=="index.php" ) continue;
		$dir[] = $file;
	}
	closedir($dir_h);

	uasort($dir, "cmp_filetime");
	print("<html><title>Index of /get/ip</title><body><img src=\"/icons/back.gif\" alt=\"[DIR]\"></td><td><a href=\"..\">Parent Directory</a><table>");
	foreach($dir as $file){
		$s = time()-filemtime($file);
		$d = (int)($s/86400);
		$s -= $d*86400;
		$h = (int)($s/3600);
		$s -= $h*3600;
		$m = (int)($s/60);
		$s -= $m*60;
		printf("<tr><td><a href=\"$file\">OPEN</a></td><td><a href=\"http://whatismyipaddress.com/ip/$file\">CHECK</a></td><td>$d %02d:%02d:%02d</td><td>%s</td></tr>",$h,$m,$s,file_get_contents($file));
	}
	print("</table></body></html>");
?>