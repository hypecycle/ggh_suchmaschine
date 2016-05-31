

//Variablen Menschen
ms = 1.27; //Skalierung des Mannes Größter = 190 cm

boxc_r = .7;
boxc_g = .5;
boxc_b = .5;
boxc_a = 1; //Sichtbarkeit, 1 = voll

//variablen Box
box_h = 200;
box_b = 200; //Breite der Box
box_t = 80; // Tiefe der Box
box_l = 0; //Lift, im Transportbetrieb

box_d = 0.3; //Dicke der Platten in mm


//variablen Geruest

//Farbe
gerc_r = .7;
gerc_g = .8;
gerc_b = .7;
gerc_a = 1; //Sichtbarkeit, 1 = voll


holz_b = 2.4; //Kantholz, 1 = voll
holz_l = 3.8;

//Variablen Monitor

monitor_b = 30;
monitor_h = 22;

monitor_z =150;

//Aufruf


geruest_vorne_hinten();
geruest_seiten();
//box();  //-Schraegstriche entfernen um box zu zeigen
//people_stand(); //-Schraegstriche entfernen um Menschen zu zeigen
//people_walk(); //-Schraegstriche entfernen um Menschen zu zeigen

module people_stand()
{
    difference()
	{
       	union()
        {   
            //Mann 1
            translate([90,0,-4])
            scale([ms,ms,ms])
            rotate([0,0,90])
            import("man_1.stl", convexity=3);
            //Mann 2
            translate([105,60,-4])
            scale([ms,ms,ms])
            rotate([0,0,90])
            import("man_3.stl", convexity=3);
            //Mann 3
            translate([60,60,-4])
            scale([ms,ms,ms])
            rotate([0,0,90])
            import("man_2.stl", convexity=3);
            //Mann 3
            translate([90,120,-4])
            scale([ms,ms,ms])
            rotate([0,0,90])
            import("man_2.stl", convexity=3);
        }
        
         union()
        {
            translate([0,0,-5])
            cube([200, 500, 5]);
        }
    }
}

module people_walk()
{
    difference()
	{
       	union()
        {   
            //Mann 1
            translate([0,0,-4])
            scale([ms,ms,ms])
            rotate([0,0,0])
            import("man_1.stl", convexity=3);
            //Mann 2
            translate([0,60,-4])
            scale([ms,ms,ms])
            rotate([0,0,0])
            import("man_3.stl", convexity=3);
            //Mann 3
            translate([0,120,-4])
            scale([ms,ms,ms])
            rotate([0,0,0])
            import("man_2.stl", convexity=3);
        }
        
         union()
        {
            translate([0,0,-5])
            cube([200, 500, 5]);
        }
    }
}


module geruest_vorne_hinten()
{
    difference()
	{
       	union()
        {
            //Hinterseite Box links hinten
            translate([box_d,box_d, holz_l])
            color([gerc_r, gerc_g, gerc_b, gerc_a])
            cube([holz_b,holz_l,box_h - box_d - holz_l * 2]);
            
            //Hinterseite Box rechts hinten
            translate([box_d,box_b - box_d - holz_l,holz_l])
            color([gerc_r, gerc_g, gerc_b, gerc_a])
            cube([holz_b,holz_l,box_h - box_d - holz_l * 2]);

            //Hinterseite Box unten
            translate([box_d,box_d, 0])
            color([gerc_r, gerc_g / 2, gerc_b, gerc_a])
            cube([holz_b, box_b - box_d * 2, holz_l]);
            
            //Hinterseite Box oben
            translate([box_d,box_d,box_h - box_d - holz_l])
            color([gerc_r, gerc_g / 2, gerc_b, gerc_a])
            cube([holz_b, box_b - box_d * 2, holz_l]);
            
            
            //Vorderseite Box links vorn
            translate([box_t - box_d - holz_b,box_d, holz_l])
            color([gerc_r, gerc_g, gerc_b, gerc_a])
            cube([holz_b,holz_l,box_h - box_d - holz_l * 2]);
            
            //Vorderseite Box rechts vorn
            translate([box_t - box_d - holz_b,box_b - box_d - holz_l, holz_l])
            color([gerc_r, gerc_g, gerc_b, gerc_a])
            cube([holz_b,holz_l,box_h - box_d - holz_l * 2]);
            
            //Vorderseite Box unten
            translate([box_t - box_d - holz_b, box_d, 0])
            color([gerc_r, gerc_g / 2, gerc_b, gerc_a])
            cube([holz_b, box_b - box_d * 2, holz_l]);

            //Vorderseite Box oben
            translate([box_t - box_d - holz_b, box_d ,box_h - box_d - holz_l])
            color([gerc_r, gerc_g / 2, gerc_b, gerc_a])
            cube([holz_b, box_b - box_d * 2, holz_l]);
            
            
            //Monitorstrebe unten
            translate([box_t - box_d - holz_b, box_d + holz_l, monitor_z - holz_l])
            color([gerc_r, gerc_g / 2, gerc_b, gerc_a])
            cube([holz_b, box_b - box_d * 2 - holz_l*2, holz_l]);
            
            //Monitorstrebe oben
            translate([box_t - box_d - holz_b, box_d + holz_l, monitor_z + monitor_h])
            color([gerc_r, gerc_g / 2, gerc_b, gerc_a])
            cube([holz_b, box_b - box_d * 2 - holz_l*2, holz_l]);
            
        }
        
         union()
        {
            //Elemente Minus
        }
    }
}


module geruest_seiten()
{
    difference()
	{
       	union()
        {
            //Linke Seite unten
            translate([box_d + holz_b,box_d,0])
            color([gerc_r/2, gerc_g, gerc_b, gerc_a])
            cube([box_t - box_d*2 - holz_b * 2 ,holz_b, holz_l]);
            
            //Linke Seite oben
            translate([box_d + holz_b,box_d,box_h - holz_l - box_d])
            color([gerc_r/2, gerc_g, gerc_b, gerc_a])
            cube([box_t - box_d*2 - holz_b * 2 ,holz_b, holz_l]);
            
            //linke Seiten hinten
            translate([box_d + holz_b,box_d, holz_l])
            color([gerc_r, gerc_g, gerc_b/2, gerc_a])
            cube([holz_l,holz_b,box_h - box_d - holz_l * 2]);

            //linke Seiten vorn
            translate([box_t - box_d - holz_l - holz_b ,box_d, holz_l])
            color([gerc_r, gerc_g, gerc_b/2, gerc_a])
            cube([holz_l,holz_b,box_h - box_d - holz_l * 2]);
            
            //rechte Seite unten
            translate([box_d + holz_b,box_b - holz_b - box_d,0])
            color([gerc_r/2, gerc_g, gerc_b, gerc_a])
            cube([box_t - box_d*2 - holz_b * 2 ,holz_b, holz_l]);
            
            //rechte Seite oben
            translate([box_d + holz_b,box_b - holz_b - box_d,box_h - holz_l - box_d])
            color([gerc_r/2, gerc_g, gerc_b, gerc_a])
            cube([box_t - box_d*2 - holz_b * 2 ,holz_b, holz_l]);
            
            //rechte Seiten hinten
            translate([box_d + holz_b,box_b - holz_b - box_d, holz_l])
            color([gerc_r, gerc_g / 2, gerc_b / 2, gerc_a])
            cube([holz_l,holz_b,box_h - box_d - holz_l * 2]);
            
            //rechte Seiten vorn
            translate([box_t - box_d - holz_l - holz_b ,box_b - holz_b - box_d, holz_l])
            color([gerc_r, gerc_g, gerc_b/2, gerc_a])
            cube([holz_l,holz_b,box_h - box_d - holz_l * 2]);
            

            
        }
        
         union()
        {
            
        }
    }
}

module box()
{
    difference()
	{
       	union()
        {
            //Platten vorn
            color([boxc_r * .75, boxc_g * .5, boxc_b,boxc_a])
            translate([0,0,box_l])
            cube([box_d,box_b,box_h]);       
       
            //Platten hinten
            color([boxc_r * .75, boxc_g * .5, boxc_b,boxc_a])
            translate([box_t - box_d,0,box_l])
            cube([box_d,box_b,box_h]);  
            
            //Platten rechts
            color([boxc_r, boxc_g, boxc_b, boxc_a])
            translate([box_d,0,box_l])
            cube([box_t - box_d*2,box_d,box_h]);      
    
            //Platten links
            color([boxc_r, boxc_g, boxc_b, boxc_a])
            translate([box_d,box_b-box_d,box_l])
            cube([box_t - box_d*2,box_d,box_h]);       

            //Platten oben
            color([boxc_r * .7, boxc_g * .7, boxc_b * .7, boxc_a])
            translate([box_d,box_d,box_h - box_d])
            cube([box_t - 2 * box_d,box_b - 2 * box_d,box_d]); 


        }
        
         union()
        {
            //Elemente Minus
            translate([box_t - 1, box_b / 2 - monitor_b / 2,  monitor_z])
            cube([box_d + 2, monitor_b,  monitor_h]);
            
        }
    }
}