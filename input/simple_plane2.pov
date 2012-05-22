camera {
   location  <0, 0, -14>
   up        <0,  1,  0>
   right     <1, 0,  0>
   look_at   <0, 0, -13>
}

light_source {<0, 1, 0> color rgb <1.5, 1.5, 1.5>}

sphere {1.0
   pigment {color rgb <0.09, 0.12, 0.90>}
   finish {ambient 0.2 diffuse 0.4}
   translate <0.0, 1.0, 0.0>
}

sphere {1.0
   pigment {color rgb <0.3, 0.7, 0.97>}
   finish {ambient 0.2 diffuse 0.4}
   translate <-2.0, 0.0, 0.0>
}

sphere {1.0
   pigment {color rgb <0.11, 0.22, 0.55>}
   finish {ambient 0.2 diffuse 0.4}
   translate <2.0, -1.0, 0.0>
}

box {0.75
   pigment {color rgb <0.57, 0.18, 0.08>}
   finish {ambient 0.2 diffuse 0.4}
   scale <0.8, 2.0, 1.0>
   rotate 30 <0, 0, 1>
   rotate 15 <0, 1, 0>
}

plane {<0.0, 1.0, 0.0>, -2.0
   pigment {color rgb <0.63, 0.91, 0.69>}
   finish {ambient 0.2 diffuse 0.4}
}
