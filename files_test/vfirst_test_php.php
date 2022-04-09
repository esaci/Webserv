
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="fr">
  <head>
    <title>Ca marche !</title>
  </head>
  <body>
  <?php
  echo '<strong>LE CGI FONCTIONNE  !</strong>';
  $rp15 = htmlspecialchars($_POST['rp15']);
  $brp15  = htmlspecialchars($_POST['brp15']);

  echo  'Tu penses donc que Raphifou15 est forcement ', $rp15, ' , Ah bon ??? ', $brp15;
?>
  </body>
</html>