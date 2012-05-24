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
   translate <2.0, 0.0, 0.0>
}

plane {<0.0, 1.0, 0.0>, -1.0
   pigment {color rgb <0.63, 0.91, 0.69>}
   finish {ambient 0.2 diffuse 0.4}
}
