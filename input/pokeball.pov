camera {
   location  <0, 0, -14>
   up        <0,  1,  0>
   right     <1.5, 0,  0>
   look_at   <0, 0, 0>
}

light_source {<-10, 10, -10> color rgb <1.5, 1.5, 1.5>}
light_source {<6, 1, -5> color rgb <1.5, 1.5, 1.5>}

// Lower half.
sphere {<0, 0, 0>, 2.0
   pigment {color rgb <0.937, 0.933, 0.918>}
   finish {ambient 0.2 diffuse 0.4 specular 0.6 roughness 0.01}
   rotate 30 <1, 0, 0>
   rotate 20 <0, 1, 0>
   mod 10.0
   subtract sphere {<0, 1.6, 0>, 2.0
      scale <2.0, 1.0, 2.0>
   }
}

// Upper half.
sphere {<0, 0, 0>, 2.0
   pigment {color rgb <0.824, 0.0196, 0.0392>}
   finish {ambient 0.2 diffuse 0.6 specular 0.8 roughness 0.01}
   rotate 30 <1, 0, 0>
   rotate 20 <0, 1, 0>
   mod 10.0
   subtract sphere {<0, -1.6, 0>, 2.0
      scale <2.0, 1.0, 2.0>
   }
}

// Inner sphere.
sphere {<0, 0, 0>, 1.85
   pigment {color rgb <0.12, 0.12, 0.12>}
   finish {ambient 0.2 diffuse 0.5 specular 0.3 roughness 0.1}
   rotate 30 <1, 0, 0>
   rotate 20 <0, 1, 0>
   mod 10.0
}

// Front sphere.
sphere {<0, 0, 0>, 0.14
   pigment {color rgb <0.12, 0.12, 0.12>}
   finish {ambient 0.2 diffuse 0.2 specular 0.1 roughness 0.2}
   rotate 30 <1, 0, 0>
   rotate 20 <0, 1, 0>
   translate <0, 0, -2>
   scale <4.0, 4.0, 1.0>
   mod 10.0
   subtract sphere {<0, 0, 0>, 0.325
      scale <0.25, 0.25, 5.0>
   }
}

// Front inner sphere.
sphere {<0, 0, 0>, 0.12
   pigment {color rgb <0.2, 0.2, 0.2>}
   finish {ambient 0.2 diffuse 0.4 specular 0.4 roughness 0.05}
   rotate 30 <1, 0, 0>
   rotate 20 <0, 1, 0>
   translate <0, 0, -2>
   scale <4.0, 4.0, 1.0>
   mod 10.0
}
