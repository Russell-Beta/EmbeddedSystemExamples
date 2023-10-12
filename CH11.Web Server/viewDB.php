<html>
<title> [ PHP & Raspberry Pi ] </title>
<body>
<script language='javascript'>
    window.setTimeout('window.location.reload()', 1000);
</script>
<h3> PHP & MySQL View </h3>
<?php
//- raspiDB 관련 변수 선언 -----------------------------------------------------
$db_host = "  ";
$db_user = "root";
$db_passwd = "root";
$db_name = " ";
$db_port = 3306 ;
//- raspiDB 연결 -----------------------------------------------------------------
echo "(1) DB Connecting -----------------------<br>";
$conn = mysqli_connect( $db_host, $db_user, $db_passwd, $db_name,
$db_port );
if(!$conn) {
    echo " \tDB Connect : Fail ~!! [ " . mysqli_connect_errno() . " ] \t";
    echo mysqli_connect_error() . "<br><br>";
}else {
    echo " \tDB Connected. OK~!!<br><br>";
}
//- raspiDB 데이터 조회-------------------------------------------
echo "(2) DB Query ---------------------------------<br>";
$query = "select * from sensor";
$result = mysqli_query($conn, $query);
$rows = mysqli_num_rows($result);
echo "Rows = " . $rows."<br><br>";
//- Disconnect ------------------------------------------------------
    echo "(3) DB Disconnect ----------------------<br>";
    mysqli_free_result($result);
    mysqli_close($connect);
    echo " \tDB Disconnect OK ~ !!<br>";
?>
</body>
</html>
