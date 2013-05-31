<?php

	function ip(){
		$ip_keys = array('HTTP_CLIENT_IP', 'HTTP_X_FORWARDED_FOR', 'HTTP_X_FORWARDED', 'HTTP_X_CLUSTER_CLIENT_IP', 'HTTP_FORWARDED_FOR', 'HTTP_FORWARDED', 'REMOTE_ADDR');
		foreach($ip_keys as $key){
			if(array_key_exists($key, $_SERVER)===true){
				foreach(explode(',', $_SERVER[$key]) as $ip){
					$ip = trim($ip);
					if(ip_validate($ip)) return $ip;
				}
			}
		}
		return isset($_SERVER['REMOTE_ADDR'])?$_SERVER['REMOTE_ADDR']:"ERROR";
	}

	function ip_validate($ip){
		if(filter_var($ip, FILTER_VALIDATE_IP, FILTER_FLAG_IPV4 | FILTER_FLAG_NO_PRIV_RANGE | FILTER_FLAG_NO_RES_RANGE)===false) return false;
		return true;
	}

	$user_file = $_GET["d"]."/ip/";
	$user_file.= ip();
	if(file_exists($user_file) === false){
		$ref = $_SERVER['HTTP_REFERER'];
		$pos = strpos($ref, "from=search");
		if($pos === false){
			$pos = strpos($ref, "?");
			if($pos === false) $src = "super_search";
			else $src = $ref;
		} else{
			$pos = strpos($ref, "another_condition");
			if($pos === false){
				$pos = strpos($ref, "another_one");
				if($pos === false) $src = "search";
				else $src = "another_one";
			} else $src = "another_condition";
		}
		file_put_contents($user_file, $src);
		chmod($user_file, 0600);
		if($ref != $src){
			$ref_file = $_GET["d"]."/ref/".$src;
			$ref_count = @file_get_contents($ref_file)+1;
			file_put_contents($ref_file, $ref_count);
		} else{
			$ref_file = $_GET["d"]."/ref/other";
			file_put_contents($ref_file, $ref, FILE_APPEND | LOCK_EX);
		}
	} else{
		$src_old = @file_get_contents($user_file);
		file_put_contents($user_file, $src_old);
	}

////////////////////////////////////////////////////////////////////////////////////////////////////

	header("Content-Type: image/png");
	$im = @imagecreate(1, 1) or die();
	imagecolorallocate($im, 255, 255, 255);
	imagepng($im);
	imagedestroy($im);
?>