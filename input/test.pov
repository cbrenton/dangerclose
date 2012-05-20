camera {
   location  <0, 0, -14>
   up        <0,  1,  0>
   right     <1.33333, 0,  0>
   look_at   <0, 0, 0>
}

light_source {<0, 1, 0> color rgb <1.5, 1.5, 1.5>}

sphere {0.1
   pigment {color rgb <1.0, 0.0, 0.0>}
   finish {ambient 0.2 diffuse 0.4}
   translate <0.1, 0, 1.6>
   rotate 10 <0, 1, 0>
}

sphere {0.1
   pigment {color rgb <0.0, 1.0, 0.0>}
   finish {ambient 0.2 diffuse 0.4}
}

box {0.075
   pigment {color rgb <0.0, 0.0, 1.0>}
   finish {ambient 0.2 diffuse 0.4}
   scale <0.8, 2.0, 1.0>
   rotate 30 <0, 0, 1>
   rotate 15 <0, 1, 0>
}

plane {<0.0, 1.0, 0.0>, -0.1
   pigment {color rgb <1.0, 0.0, 1.0>}
   finish {ambient 0.2 diffuse 0.4}
}
