# Before `make install' is performed this script should be runnable with
# `make test'. After `make install' it should work as `perl test.pl'

######################### We start with some black magic to print on failure.

# Change 1..1 below to 1..last_test_to_print .
# (It may become useful if the test is moved to ./t subdirectory.)

BEGIN { $| = 1; print "1..1\n"; }
END {print "not ok 1\n" unless $loaded;}
use G2;

$loaded = 1;
print "ok 1\n";

######################### End of black magic.

# Insert your test code below (better if it prints "ok 13"
# (correspondingly "not ok 13") depending on the success of chunk 13
# of the test code):

$d = newvd G2::Device();

$dev[1] = newX11 G2::Device(775, 575);
$d->attach($dev[1]);

$dev[2] = newGIF G2::Device("test.gif", 775, 575);
$d->attach($dev[2]);
	
$dev[0] = newPS  G2::Device("test.ps", 4, 0);
$d->attach($dev[0]);

$d->set_auto_flush(0);
	
for($i=0;$i<27;$i++) {
	$d->pen($i);
	$d->filled_circle($i*20+10, 10, 10); 
	$d->pen(1);
	$d->circle($i*20+10, 10, 10);
	$str = sprintf("%d", $i);
	$d->string($i*20+7, 21, $str);
    }

for($j=0;$j<$#dev;$j++)
        {
	if($dev[$j] > 0)
            {
	    for($i=0;$i<=64;$i++) {
		$dev[$j]->move( 2*$i+575, 5);
		$dev[$j]->pen($dev[$j]->ink($i/64., 0, 0));
		$dev[$j]->line_r(0, 20);
		$dev[$j]->pen($dev[$j]->ink(0, $i/64., 0));
		$dev[$j]->line_r(10, 20);
		$dev[$j]->pen($dev[$j]->ink(0, 0, $i/64.));
		$dev[$j]->line_r(-10, 20);
		}
	    }
	}

    $d->pen(1);
    $d->line(200, 50, 350, 50);
    $d->line(200, 48, 350, 48);
    $d->line(200, 46, 350, 46);
    $d->line(200, 46, 200, 75);
    $d->line(198, 46, 198, 75);
    $d->line(196, 46, 196, 75);
    $d->string(200, 50, "012abcABC#())(\\-+~*!$%&");
    $d->pen(1);
    for($i=1;$i<25;$i++) {
	$d->line(15, $i*20+50, 15, $i*20+50+$i);
	$d->set_font_size(12);
	$str = sprintf("%2d:", $i);
	$d->string(20, $i*20+50, $str);
	$d->set_font_size($i);
	$d->string(40, $i*20+50, "hello, world");
    }

    $d->plot(150, 70);
    $d->line(147, 68, 153, 68);
		
    $y=100;
    $d->line(100, $y, 150, $y+50);
    $d->triangle(150, $y, 250, $y, 200, $y+50);
    $d->rectangle(300, $y, 400, $y+50);
    $d->circle(450, $y+25, 25);
    $d->ellipse(550, $y+25, 45, 25);
    $d->arc(650, $y+25, 25, 45, 90, 360);
    
    $y=200;
    $d->filled_triangle(150, $y, 250, $y, 200, $y+50);
    $d->filled_rectangle(300, $y, 400, $y+50);
    $d->filled_circle(450, $y+25, 25);
    $d->filled_ellipse(550, $y+25, 45, 25);
    $d->filled_arc(650, $y+25, 25, 45, 90, 360);

    $y=300.;
    $pts[0]=150.; $pts[1]=$y;
    $pts[2]=175.; $pts[3]=$y+100.;
    $pts[4]=200.; $pts[5]=$y;
    $pts[6]=225.; $pts[7]=$y+100.;
    $pts[8]=250.; $pts[9]=$y;
    $d->poly_line(5, \@pts);
    
    $pts[0]=300; $pts[1]=$y;
    $pts[2]=350; $pts[3]=$y;
    $pts[4]=375; $pts[5]=$y+50;
    $pts[6]=325; $pts[7]=$y+90;
    $pts[8]=275; $pts[9]=$y+50;
    $d->polygon(5, \@pts);

    $pts[0]=450; $pts[1]=$y;
    $pts[2]=500; $pts[3]=$y;
    $pts[4]=525; $pts[5]=$y+50;
    $pts[6]=475; $pts[7]=$y+90;
    $pts[8]=425; $pts[9]=$y+50;
    $d->filled_polygon(5, \@pts);

    
    $d->line(225, 448, 200+19*25, 448);
    for($i=1;$i<20;$i++) {
	$d->set_line_width($i);
	$d->move(200+$i*25, 450);
	$d->line_to(200+$i*25, 550);
    }

    $d->set_line_width(5);
    for($i=1;$i<10;$i++) {
	$pts[0]=1*$i;
	$pts[1]=2*$i;
	$pts[2]=3*$i;
	$d->set_dash(3, \@pts);
	$d->line(550, 300+$i*8, 750, 350+$i*8); 
    }

    $d->set_dash(0);
    $d->set_line_width(5);
    $d->arc(740, 180, 25, 100, -45+15, -45-15);
    $d->filled_arc(740, 180, 12, 50, -45+15, -45-15);

    $d->flush;
    print "\nDone.\n[Enter]\n";
    getc(STDIN);
    $d->close();
