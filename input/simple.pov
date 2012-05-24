camera {
   location  <0, 0, -14>
   up        <0,  1,  0>
   right     <1, 0,  0>
   look_at   <0, 0, -13>
}

light_source {<0, 1, 0> color rgb <1.5, 1.5, 1.5>}

sphere {1.0
   pigment {color rgb <1.0, 0.0, 0.0>}
   finish {ambient 0.2 diffuse 0.4}
   translate <1.0, 0.0, 0.0>
}

sphere {1.0
   pigment {color rgb <1.0, 0.0, 0.0>}
   finish {ambient 0.2 diffuse 0.4}
   translate <-1.0, 0.0, 0.0>
}
