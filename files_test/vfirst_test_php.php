<?php
  // The global $_POST variable allows you to access the data sent with the POST method by name
  // To access the data sent with the GET method, you can use $_GET
  $rp15 = htmlspecialchars($_POST['rp15']);
  $brp15  = htmlspecialchars($_POST['brp15']);

  echo  'Tu penses donc que Raphifou15 est forcement ', $rp15, ' , Ah bon ??? ', $brp15;
?>