#include "nyuparser.h"
#include "scene.h"

using namespace std;

/* a collection of functions for syntax verification */

void NYUParser::ParseLeftAngle(){
   // GetToken();
   Token t = tokenizer->GetToken();
   if(t.id != T_LEFT_ANGLE ) tokenizer->Error("Expected <");
}

void NYUParser::ParseRightAngle()
{
   // GetToken();
   Token t = tokenizer->GetToken();
   if(t.id != T_RIGHT_ANGLE ) tokenizer->Error("Expected >");
}

double NYUParser::ParseDouble()
{
   // GetToken();
   Token t = tokenizer->GetToken();
   if(t.id != T_DOUBLE ) tokenizer->Error("Expected a number");
   return t.double_value;
}

void NYUParser::ParseLeftCurly()
{
   // GetToken();
   Token t = tokenizer->GetToken();
   if(t.id != T_LEFT_CURLY ) tokenizer->Error("Expected {");
}

void NYUParser::ParseRightCurly()
{
   // GetToken();
   Token t = tokenizer->GetToken();
   if(t.id != T_RIGHT_CURLY ) tokenizer->Error("Expected }");
}

void NYUParser::ParseComma()
{
   // GetToken();
   Token t = tokenizer->GetToken();
   if(t.id != T_COMMA ) tokenizer->Error("Expected ,");
}

void NYUParser::ParseVector(glm::vec3 & v)
{
   ParseLeftAngle();
   v[0] = ParseDouble();
   ParseComma();
   v[1] = ParseDouble();
   ParseComma();
   v[2] = ParseDouble();
   ParseRightAngle();
}

void NYUParser::ParseRGBFColor(glm::vec3 & c, float & f)
{
   ParseLeftAngle();
   c[0] = ParseDouble();
   ParseComma();
   c[1] = ParseDouble();
   ParseComma();
   c[2] = ParseDouble();
   ParseComma();
   f = ParseDouble();
   ParseRightAngle();
}

void NYUParser::ParseRGBColor(glm::vec3 & c, float & f)
{
   ParseLeftAngle();
   c[0] = ParseDouble();
   ParseComma();
   c[1] = ParseDouble();
   ParseComma();
   c[2] = ParseDouble();
   f = 0.0;
   ParseRightAngle();
}

void NYUParser::ParseColor(glm::vec3 & c, float & f)
{
   // GetToken();
   Token t = tokenizer->GetToken();
   if(t.id == T_RGB)
      ParseRGBColor(c, f);
   else if ( t.id == T_RGBF )
      ParseRGBFColor(c, f);
   else tokenizer->Error("Expected rgb or rgbf");
}

void NYUParser::PrintColor(glm::vec3 & c, float & f)
{
   cout << "rgbf <" << c[0] << "," << c[1] << "," << c[2] << "," << f << ">" << endl;
}

void NYUParser::ParseMatrix(){
   cout << "Error: Cannot Parse Matrix" << endl;
   exit(0);
}

void NYUParser::ParseTransform(Geometry & s)
{
   /* if there is nothing to parse, this is not our problem:
      this should be handled by the caller */
   glm::vec3 v;
   Token t;
   double angle;
   for(;;){
      t = tokenizer->GetToken();
      switch( t.id )
      {
      case T_SCALE:
         ParseVector(v);
         s.addScale(v);
         break;
      case T_ROTATE:
         angle = ParseDouble();
         ParseVector(v);
         s.addRotate(angle, v);
         break;
      case T_TRANSLATE:
         ParseVector(v);
         s.addTranslate(v);
         break;
         /* once we run into an unknown token, we assume there are no
            more  transforms to parse and we return to caller */
      case T_MATRIX:
         ParseMatrix();
         break;
      default: tokenizer->UngetToken(); return;
      }
   }
}

void NYUParser::ParsePigment(Material & p)
{
   Token t;
   ParseLeftCurly();
   for(;;)
   {
      t = tokenizer->GetToken();
      float f = 0.0f;
      if( t.id == T_COLOR)
         ParseColor(p.color, f);
      else if( t.id == T_RIGHT_CURLY) return;
      else tokenizer->Error("error parsing pigment: unexpected token");
   }
}

void NYUParser::PrintPigment(Material & p){
   printf("\tpigment { color ");
   float f = 0.0f;
   PrintColor(p.color, f);
   printf("}");
}

void NYUParser::ParseFinish(Material & f)
{
   Token t;
   ParseLeftCurly();
   f.rough = 0.05;
   for(;;)
   {
      // GetToken();
      t = tokenizer->GetToken();
      switch(t.id){
      case T_AMBIENT:
         f.kA = ParseDouble();
         break;
      case T_DIFFUSE:
         f.kD = ParseDouble();
         break;
      case T_PHONG:
         // finish->phong = ParseDouble();
         cout << "Error: phong not supported" << endl;
         break;
      case T_PHONG_SIZE:
         // finish->phong_size = ParseDouble();
         cout << "Error: phong size not supported" << endl;
         break;
      case T_REFLECTION:
         //f.reflection = ParseDouble();
         cout << "Error: reflection not supported" << endl;
         break;
      case T_METALLIC:
         // finish->metallic = ( ParseDouble()!= 0.0 ? 1: 0);
         cout << "Error: metallic not supported" << endl;
         break;
         // added by mbecker
      case T_REFRACTION:
         //f.refraction = ParseDouble();
         cout << "Error: refraction not supported" << endl;
         break;
         // added by mbecker
      case T_SPECULAR:
         f.kS = ParseDouble();
         break;
      case T_ROUGHNESS:
         f.rough = ParseDouble();
         break;
      case T_RIGHT_CURLY: return;
      default: tokenizer->Error("Error parsing finish: unexpected token");
      }
   }
}

void NYUParser::PrintFinish(Material & f){
   /*
      printf("\tfinish { ambient %.3g diffuse %.3g phong %.3g phong_size %.3g reflection %.3g metallic %d }\n",
      finish->ambient, finish->diffuse,
      finish->phong, finish->phong_size,
      finish->reflection, finish->metallic);
      */
   cout << "\tfinish {";
   cout << " ambient " << f.kA;
   cout << " diffuse " << f.kD;
   cout << " specular " << f.kS;
   cout << " roughness " << f.rough;
   //cout << " reflection " << f.reflection;
   //cout << " refraction " << f.refraction;
   //cout << " ior " << f.ior << " }" << endl;
}

// void NYUParser::ParseInterior( struct Interior* interior){
void NYUParser::ParseInterior(float & ior){
   Token t;
   ParseLeftCurly();
   // while[1]{
   for(;;)
   {
      // GetToken();
      t = tokenizer->GetToken();
      if( t.id == T_RIGHT_CURLY) return;
      else if (t.id == T_IOR)
      {
         // interior->ior = ParseDouble();
         ior = ParseDouble();
      } else tokenizer->Error("Error parsing interior: unexpected token\n");
   }
}

/*
   void NYUParser::InitModifiers(struct ModifierStruct* modifiers)
   {

   SetIdentity4d(&(modifiers->transform));

   modifiers->pigment.color[0] = 0;
   modifiers->pigment.color[1] = 0;
   modifiers->pigment.color[2] = 0;
   modifiers->pigment.color.f = 0;

   modifiers->finish.ambient    = 0.1;
   modifiers->finish.diffuse    = 0.6;
   modifiers->finish.phong      = 0.0;
   modifiers->finish.phong_size = 40.0;
   modifiers->finish.reflection = 0;

   modifiers->interior.ior = 1.0;
   }
   */

void NYUParser::ParseSubtract(Geometry & s)
{
   Token t = tokenizer->GetToken();

   if(t.id != T_EOF)
   {
      switch(t.id)
      {
      case T_SPHERE:
         s.csg_sub = ParseSphere();
         break;
      case T_BOX:
         s.csg_sub = ParseBox();
         break;
      default:
         tokenizer->Error("Unknown statement");
      }
   }
}

void NYUParser::ParseIntersect(Geometry & s)
{
   Token t = tokenizer->GetToken();

   if(t.id != T_EOF)
   {
      switch(t.id)
      {
      case T_SPHERE:
         s.csg_int = ParseSphere();
         break;
      case T_BOX:
         s.csg_int = ParseBox();
         break;
      default:
         tokenizer->Error("Unknown statement");
      }
   }
}

void NYUParser::ParseUnion(Geometry & s)
{
   Token t = tokenizer->GetToken();

   if(t.id != T_EOF)
   {
      switch(t.id)
      {
      case T_SPHERE:
         s.csg_un = ParseSphere();
         break;
      case T_BOX:
         s.csg_un = ParseBox();
         break;
      default:
         tokenizer->Error("Unknown statement");
      }
   }
}

void NYUParser::ParseModifiers(Geometry & s){
   Token t;
   for(;;)
   {
      // GetToken();
      t = tokenizer->GetToken();
      switch(t.id)
      {
      case  T_SCALE:
      case T_ROTATE:
      case T_TRANSLATE:
      case T_MATRIX:
         tokenizer->UngetToken();
         // ParseTransform(&(modifiers->transform));
         ParseTransform(s);
         break;
      case T_PIGMENT:
         // ParsePigment(&(modifiers->pigment));
         ParsePigment(s.mat);
         break;
      case T_FINISH:
         // ParseFinish(&(modifiers->finish));
         ParseFinish(s.mat);
         break;
      case T_SUBTRACT:
         //tokenizer->UngetToken();
         ParseSubtract(s);
         break;
      case T_MOD:
         s.modDist = ParseDouble();
         s.isMod = true;
         break;
         /*
            case T_INTERIOR:
         // ParseInterior(&(modifiers->interior));
         ParseInterior(s.f.ior);
         break;
         */
      default: tokenizer->UngetToken(); return;
      }
   }
}

void NYUParser::PrintModifiers(Geometry & s){
   /*
      printf("\tmatrix "); PrintMatrix4d(modifiers->transform);
      printf("\n");
      PrintPigment(&(modifiers->pigment));
      printf("\n");
      PrintFinish(&(modifiers->finish));
      printf("\tinterior { ior %.3g }\n", modifiers->interior.ior);
      */
   PrintPigment(s.mat);
   cout << "\n" << endl;
   PrintFinish(s.mat);
   cout << "\n" << endl;
}


Camera NYUParser::ParseCamera()
{
   /* these are variables where we store the information about the
      camera; they can be used in the end of the function to
      assign fields in the camera object */

   glm::vec3 location, right, up, look_at;
   //double angle;
   // struct Matrix4d  transform;
   bool done = false;
   Token t;
   // SetIdentity4d(&transform);

   /* default values */
   /*
      SetVect(&location, 0.0, 0.0,0.0);
      SetVect(&look_at, 0.0, 0.0,1.0);
      SetVect(&right, 1.0, 0.0, 0.0);
      SetVect(&up, 0.0,1.0,0.0);
      angle = 60.0*M_PI/180.0;
      */

   ParseLeftCurly();

   /* parse camera parameters */
   while(!done)
   {
      // GetToken();
      t = tokenizer->GetToken();
      switch(t.id)
      {
      case T_LOCATION:  ParseVector(location);  break;
      case T_RIGHT:     ParseVector(right);     break;
      case T_UP:        ParseVector(up);        break;
      case T_LOOK_AT:   ParseVector(look_at);   break;
                        //case T_ANGLE:     angle = M_PI*ParseDouble()/180.0;   break;
      default: done = true; tokenizer->UngetToken(); break;
      }
   }

   // ParseTransform(&transform); // NOTE: may need this!
   ParseRightCurly();

   /* TODO: assignment to the camera object fields should happen here;
      for now, we just print the values */

   // printf("camera { \n");
   // printf("\tlocation ");   PrintVect(location);   printf("\n");
   // printf("\tright ");      PrintVect(right);      printf("\n");
   // printf("\tup ");         PrintVect(up);         printf("\n");
   // printf("\tangle %.3g\n", angle*180.0/M_PI);
   // printf("\tlook_at ");   PrintVect(look_at);   printf("\n");
   // printf("\tmatrix "); PrintMatrix4d(transform);
   // printf("\n}\n");
   glm::vec3 lookDir = glm::normalize(look_at - location);
   return Camera(location,up,right,location + lookDir);
   //return Camera(location,up,right,look_at);
}

Sphere * NYUParser::ParseSphere()
{
   ParseLeftCurly();
   glm::vec3 translateVec;
   ParseVector(translateVec);
   ParseComma();
   Sphere * s = new Sphere(ParseDouble());
   s->addTranslate(translateVec);

   ParseModifiers(*s);
   ParseRightCurly();

   return s;
}

Box * NYUParser::ParseBox(){
   ParseLeftCurly();
   Box *b = new Box(ParseDouble());
   ParseModifiers(*b);
   ParseRightCurly();

   return b;
}

void NYUParser::ParseCylinder(){
   cout << "Error: Cannot parse cylinder" << endl;
   exit(0);
}

/*
   Cone * NYUParser::ParseCone(){
// struct Vector base_point, cap_point;
glm::vec3 base_point, cap_point;
double base_radius, cap_radius;
// struct ModifierStruct modifiers;
// InitModifiers(&modifiers);

Cone * c = new Cone();

// SetVect(&base_point, 0,0,0);
// SetVect(&cap_point, 0,0,0);
base_radius = 0;
cap_radius = 0;

ParseLeftCurly();
ParseVector(base_point);
ParseComma();
base_radius = ParseDouble();
ParseComma();
ParseVector(cap_point);
ParseComma();
cap_radius = ParseDouble();
ParseModifiers(*c);
ParseRightCurly();

// TODO: assignment to the cone object fields should happen here;
// for now, we just print the values

// printf("cone {\n\t");
// PrintVect(base_point); printf(", %.3g, ", base_radius);
// PrintVect(cap_point); printf(", %.3g\n",  cap_radius);
// PrintModifiers(&modifiers);
// printf("\n}\n");
}
*/

Plane * NYUParser::ParsePlane(){
   ParseLeftCurly();
   glm::vec3 normal;
   ParseVector(normal);
   ParseComma();
   Plane * p = new Plane(normal, ParseDouble());

   ParseModifiers(*p);
   ParseRightCurly();

   return p;
}

Light * NYUParser::ParseLightSource()
{
   Token t;
   glm::vec3 c;
   float f;
   glm::vec3 pos;

   c = glm::vec3(0.0f);
   f = 0.0f;
   pos[0] = 0; pos[1] = 0; pos[2] = 0;
   ParseLeftCurly();
   ParseVector(pos);
   t = tokenizer->GetToken();
   if(t.id != T_COLOR) tokenizer->Error("Error parsing light source: missing color");
   ParseColor(c, f);
   ParseRightCurly();

   return new Light(pos, c);
}

void NYUParser::ParseGlobalSettings(){
   cout << "Error: Cannot parse global settings" << endl;
   exit(0);
   /*
      struct Color ambient;
      ambient[0] = 0; ambient[1] = 0; ambient[2] = 0; ambient.f =0;
      ParseLeftCurly();
      while[1]
      {
      GetToken();
      if(Token.id == T_AMBIENT_LIGHT){
      ParseLeftCurly();
      GetToken();
      if(Token.id != T_COLOR)
      Error("Error parsing light source: missing color");
      ParseColor(&ambient);
      ParseRightCurly();
      } else if(Token.id == T_RIGHT_CURLY)
      {
      break;
      } else
      Error("error parsing default settings: unexpected token");
      }
      printf("global_settings {\n");
      printf("\tambient_light {"); PrintColor(&ambient);
      printf("\n}\n");
      */
}

/* main parsing function calling functions to parse each object;  */

void NYUParser::parse(std::fstream & input, Scene & s){
   tokenizer = new Tokenizer(input);
   Token t = tokenizer->GetToken();
   Sphere * sphere;
   Box * box;
   // Cone * cone;

   // added by mbecker
   Plane * plane;

   // GetToken();
   while(t.id != T_EOF)
   {
      switch(t.id)
      {
      case T_CAMERA:
         s.setCamera(ParseCamera());
         break;
      case T_SPHERE:
         sphere = ParseSphere();
         s.addGeom(sphere);
         break;
      case T_BOX:
         box = ParseBox();
         s.addGeom(box);
         break;
      case T_CYLINDER:
         ParseCylinder();
         break;
      case T_CONE:
         // cone = ParseCone();
         // s.gVec.push_back(cone);
         break;
      case T_PLANE:
         plane = ParsePlane();
         s.addGeom(plane);
         break;
      case T_LIGHT_SOURCE:
         //s.lights.push_back(ParseLightSource());
         s.addLight(ParseLightSource());
         break;
      case T_GLOBAL_SETTINGS:
         ParseGlobalSettings();
         break;
      default:
         tokenizer->Error("Unknown statement");
      }
      // GetToken();
      t = tokenizer->GetToken();
   }
   delete tokenizer;
}
