$fa = 1;
$fs = 0.4;

// thickness of the box walls.
wall = 2;

// height of the interlocking steps.
wall_step = 2.5;

// half the wall thickness.
half_wall = wall / 2;

// twice the wall thickness.
walls = wall * 2;

// size of the feather board.
feather_width = 22.95;
feather_length = 51;

// the wing is the same width, but longer.
wing_length = 56.2;

// the height of the two boards, not including the ethernet jack.
feather_wing_height = 9.7;

// and the size of the ethernet jack.
ethernet_width = 16.5;
ethernet_height = 13.5;

// size of the usb port.
usb_width = 8.0;
usb_height = 3.0;

usb_indent_height = 6.5;
usb_indent_width = 11;
usb_indent_depth = 0.5;

// sensor lead thickness.
lead_thickness = 3.75;
lead_from_back = 15.9;

// amount to sink into adjacent surfaces for attachment.
attach = 0.001;

// a small gap between the top plate and the feather.
// this will allow for solder joints.
top_gap = 1.25;

// the total internal height.
internal_height = ethernet_height + feather_wing_height + top_gap;

// thickness of the bottom (mounting) surface.
bottom_thickness = 2.54;

// mounts.
mount_hole = 5.5;
mount_tab = mount_hole * 2;


// overall size.
box_width = feather_width + (wall * 2);
box_length = wing_length + (wall * 2);
box_height = internal_height + bottom_thickness + wall;

// the height of the bottom portion of the box.
// the 1.6 will take it to the bottom edge of the feather itself.
// this will allow the USB slot to not need a bridge and it will
// allow the top of the box to grab the sensor wire leads.
bottom_height = internal_height + bottom_thickness - 1.6 - top_gap;

// the remainder.
top_height = box_height - bottom_height;

// type of vent holes.
vent_style = "diamond"; // "circle" (default), "square", or "diamond"

// vent dimensions
vent_hole_r = 1.3;
vent_hole_gap = 4;

echo(box_width=box_width, box_length=box_length, box_height=box_height);


// create a standoff with optional support legs.
// the standoff will be attached to whatever is directly beneath it.
// the support legs will be attached to whatever happens to be adjacent.
module standoff(height, radius, n=0, e=0, s=0, w=0, support_sub = 1) {
    translate([0, 0, -attach]) {
        cylinder(h = height + attach, r = radius);
        if (height > 1.5 && radius > 1.5) {
            if (n > 0) {
                translate([-1, 0, 0])
                    cube([2, n + radius + attach, height - support_sub]);
            }
            if (s > 0) {
                translate([-1, -s - radius - attach, 0])
                    cube([2, s + radius + attach, height - support_sub]);
            }
            if (w > 0) {
                translate([-w - radius - attach, -1, 0])
                    cube([w + radius + attach, 2, height - support_sub]);
            }
            if (e > 0) {
                translate([0, -1, 0])
                    cube([e + radius + attach, 2, height - support_sub]);
            }
        }
    }
}

module vent_hole() {
    if (vent_style == "square" || vent_style == "diamond") {
        rotate([0,0, (vent_style == "diamond") ? 45 : 0])
            translate([-vent_hole_r, -vent_hole_r, 0])
                cube([vent_hole_r * 2, vent_hole_r * 2, wall + attach * 2]);
    } else {    // "circle"
        cylinder(r = vent_hole_r, h = wall + attach * 2);
    }
}

// create rows of vent holes.
module vents(rx, ry, rw, rh) {
    px = (rw - (floor(rw / vent_hole_gap) * vent_hole_gap)) / 2;
    py = (rh - (floor(rh / vent_hole_gap) * vent_hole_gap)) / 2;
    for (y = [ry : vent_hole_gap : ry + rh + 0.001])
    {
        if (abs(round((ry - y) / (vent_hole_gap * 2)) - (ry - y) / (vent_hole_gap * 2)) > 0.01)
        {
            for (x = [rx : vent_hole_gap * 2 : rx + rw + 0.01])
            {
                translate([x + px, y + py, -attach])
                    vent_hole();
            }
        } else {
            for (x = [rx + vent_hole_gap : vent_hole_gap * 2 : rx + rw + 0.01])
            {
                translate([x + px, y + py, -attach])
                    vent_hole();
            }
        }
    }
}

module lead_cutout() {
    // the lead round hole.
    translate([0, lead_thickness / 2, lead_thickness / 2])
        rotate([0, 90, 0])    
            cylinder(r=lead_thickness / 2, h = wall + attach * 2);
    // make sure we have a smooth cutout goin up.
    translate([0, 0, lead_thickness / 2])
        cube([wall + attach * 2, lead_thickness, lead_thickness * 2]);
}

module usb_cutout() {
    union() {
        cube([usb_width, wall + (attach * 2), usb_height + attach]);
        translate([-(usb_indent_width - usb_width) / 2, wall - usb_indent_depth, -(usb_indent_height - usb_height) / 2])
            cube([usb_indent_width, usb_indent_depth + attach * 2, usb_indent_height]);
    }
}

module box_bottom(){
    translate([mount_tab, 0, 0]) {
        union(){
            difference() {
                union() {
                    cube([box_width, box_length, bottom_height - wall_step]);
                    translate([half_wall, half_wall, bottom_height - wall_step - attach])
                        cube([box_width - wall, box_length - wall, wall_step + attach]);
                    
                    // mount tabs.
                    translate([-mount_tab / 2, box_length / 2, 0])
                    {
                        cylinder(r=mount_tab / 2, h=bottom_thickness);
                        translate([0,-mount_tab / 2, 0])
                            cube([mount_tab / 2 + attach, mount_tab, bottom_thickness]);
                    }
                    translate([box_width + mount_tab / 2, box_length / 2, 0])
                    {
                        cylinder(r=mount_tab / 2, h=bottom_thickness);
                        translate([-mount_tab / 2,-mount_tab / 2, 0])
                            cube([mount_tab / 2 + attach, mount_tab, bottom_thickness]);
                    }
                }
                
                // internal cavity.
                translate([wall, wall, bottom_thickness])
                    cube([box_width - walls, box_length - walls, bottom_height]);
                
                // ethernet port.
                translate([wall + ((feather_width - ethernet_width) / 2), -attach, bottom_thickness])
                    cube([ethernet_width, wall + (attach * 2), ethernet_height]);
                
                // usb port.
                translate([wall + ((feather_width - usb_width) / 2), box_length - wall - attach, bottom_height - usb_height])
                    usb_cutout();
                
                // wire leads.
                translate([-attach, box_length - wall - lead_from_back - lead_thickness, bottom_height - lead_thickness])
                    lead_cutout();
                translate([box_width - wall - attach, box_length - wall - lead_from_back - lead_thickness, bottom_height - lead_thickness])
                    lead_cutout();
                
                // vents
                translate([wall, 0, 0])
                    rotate([0,-90,0])
                        vents(bottom_thickness, walls, bottom_height - wall_step - bottom_thickness - walls, box_length - wall * 5);
                translate([box_width, 0, 0])
                    rotate([0,-90,0])
                        vents(bottom_thickness, walls, bottom_height - wall_step - bottom_thickness - walls, box_length - wall * 5);
                    
                translate([0, box_length, 0])    
                rotate([90, 0, 0])
                    vents(walls, bottom_thickness, feather_width - walls, bottom_height - wall_step - bottom_thickness - walls);
                
                // mount holes.
                translate([-mount_tab / 2, box_length / 2, -attach])
                {
                    cylinder(r=mount_hole / 2, h=bottom_thickness + attach * 2);
                    
                }
                translate([box_width + mount_tab / 2, box_length / 2, -attach])
                {
                    cylinder(r=mount_hole / 2, h=bottom_thickness + attach * 2);
                }
            }
            translate([box_width - (wall * 3), box_length - (wall * 3), bottom_thickness - attach])
                cube([walls, walls, ethernet_height]);
        }
    }
}

module box_top() {
    union() {
        difference(){
            cube([box_width, box_length, top_height + wall_step]);
            translate([wall, wall, wall])
                cube([box_width - walls, box_length - walls, top_height + wall_step]);
            translate([half_wall, half_wall, top_height])
                cube([box_width - wall, box_length - wall, wall_step + attach]);
            // lead cutouts
            translate([-attach, box_length - wall - lead_from_back - lead_thickness, top_height]) {
                lead_cutout();
            }
            translate([box_width - wall - attach, box_length - wall - lead_from_back - lead_thickness, top_height]) {
                lead_cutout();
            }
            // usb port.
            translate([wall + ((feather_width - usb_width) / 2), box_length - wall - attach, top_height])
            usb_cutout();
        }
        translate([box_width/2, box_length - wall - feather_length, wall - attach])
        {
            translate([0, feather_length / 4, 0])
                cylinder(r=2, h=top_gap);
            translate([0, feather_length / 2, 0])
                cylinder(r=2, h=top_gap);
            translate([0, feather_length / 4 * 3, 0])
                cylinder(r=2, h=top_gap);
        }
    }
}

left_set = -box_width - mount_tab * 2 - 5;
right_set = 5;
front_set = -box_length - 8;
back_set = 8;

translate([left_set, front_set, 0])
    box_bottom();
translate([right_set + mount_tab, front_set, 0])
    box_top();

//translate([left_set + mount_tab, back_set, 0])
//    box_top();
//translate([right_set, back_set, 0])
//    box_bottom();
