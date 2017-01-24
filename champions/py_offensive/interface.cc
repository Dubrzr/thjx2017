/// This file has been generated, if you wish to
/// modify it in a permanent way, please refer
/// to the script file : gen/generator_python.rb

#include "interface.hh"

static PyObject* c_module;
static PyObject* py_module;
static PyObject* champ_module;

static void _init_python();

template <typename Lang, typename Cxx> Lang cxx2lang(Cxx in) {
  return in.__if_that_triggers_an_error_there_is_a_problem;
}

template <> PyObject* cxx2lang<PyObject*, int>(int in) {
  return PyLong_FromLong(in);
}

template <> PyObject* cxx2lang<PyObject*, double>(double in) {
  return PyFloat_FromDouble(in);
}

template <> PyObject* cxx2lang<PyObject*, std::string>(std::string in) {
  return PyUnicode_FromString(in.c_str());
}

template <> PyObject* cxx2lang<PyObject*, bool>(bool in) {
  return PyBool_FromLong(in);
}

template <typename Cxx> PyObject* cxx2lang_array(const std::vector<Cxx>& in) {
  size_t size = in.size();
  PyObject* out = PyList_New(size);

  for (unsigned int i = 0; i < size; ++i)
    PyList_SET_ITEM(out, i, (cxx2lang<PyObject*, Cxx>(in[i])));

  return out;
}

template <typename Lang, typename Cxx> Cxx lang2cxx(Lang in) {
  return in.__if_that_triggers_an_error_there_is_a_problem;
}

template <> int lang2cxx<PyObject*, int>(PyObject* in) {
  long out = PyLong_AsLong(in);
  if (PyErr_Occurred())
    throw 42;
  return out;
}

template <> double lang2cxx<PyObject*, double>(PyObject* in) {
  double out = PyFloat_AsDouble(in);
  if (PyErr_Occurred())
    throw 42;
  return out;
}

template <> bool lang2cxx<PyObject*, bool>(PyObject* in) {
  return (bool)lang2cxx<PyObject*, int>(in);
}

template <> std::string lang2cxx<PyObject*, std::string>(PyObject* in) {
  char* out = PyUnicode_AsUTF8(in);
  if (PyErr_Occurred()) {
    throw 42;
  }
  return out;
}

template <typename Cxx> std::vector<Cxx> lang2cxx_array(PyObject* in) {
  if (!PyList_Check(in)) {
    PyErr_SetString(PyExc_TypeError, "a list is required");
    throw 42;
  }

  std::vector<Cxx> out;
  unsigned int size = PyList_Size(in);

  for (unsigned int i = 0; i < size; ++i)
    out.push_back(lang2cxx<PyObject*, Cxx>(PyList_GET_ITEM(in, i)));

  return out;
}
/// Position a player can defend during a phase
template <> PyObject* cxx2lang<PyObject*, mur_position>(mur_position in) {
  PyObject* name = PyUnicode_FromString("mur_position");
  PyObject* enm = PyObject_GetAttr(py_module, name);
  if (enm == NULL)
    throw 42;
  PyObject* arglist = Py_BuildValue("(i)", (int)in);
  PyObject* ret = PyObject_CallObject(enm, arglist);
  Py_DECREF(name);
  Py_DECREF(arglist);
  Py_DECREF(enm);
  return ret;
}

template <> mur_position lang2cxx<PyObject*, mur_position>(PyObject* in) {
  return (mur_position)lang2cxx<PyObject*, int>(in);
}

/// Role played during a MUR game (attacker or defender)
template <> PyObject* cxx2lang<PyObject*, mur_role>(mur_role in) {
  PyObject* name = PyUnicode_FromString("mur_role");
  PyObject* enm = PyObject_GetAttr(py_module, name);
  if (enm == NULL)
    throw 42;
  PyObject* arglist = Py_BuildValue("(i)", (int)in);
  PyObject* ret = PyObject_CallObject(enm, arglist);
  Py_DECREF(name);
  Py_DECREF(arglist);
  Py_DECREF(enm);
  return ret;
}

template <> mur_role lang2cxx<PyObject*, mur_role>(PyObject* in) {
  return (mur_role)lang2cxx<PyObject*, int>(in);
}

/// Errors returned by the actions
template <> PyObject* cxx2lang<PyObject*, action_error>(action_error in) {
  PyObject* name = PyUnicode_FromString("action_error");
  PyObject* enm = PyObject_GetAttr(py_module, name);
  if (enm == NULL)
    throw 42;
  PyObject* arglist = Py_BuildValue("(i)", (int)in);
  PyObject* ret = PyObject_CallObject(enm, arglist);
  Py_DECREF(name);
  Py_DECREF(arglist);
  Py_DECREF(enm);
  return ret;
}

template <> action_error lang2cxx<PyObject*, action_error>(PyObject* in) {
  return (action_error)lang2cxx<PyObject*, int>(in);
}

/// Position on the NOSE grid.
template <> PyObject* cxx2lang<PyObject*, nose_position>(nose_position in) {
  PyObject* tuple = PyTuple_New(2);
  PyTuple_SET_ITEM(tuple, 0, (cxx2lang<PyObject*, int>(in.x)));
  PyTuple_SET_ITEM(tuple, 1, (cxx2lang<PyObject*, int>(in.y)));
  return tuple;
}

template <> nose_position lang2cxx<PyObject*, nose_position>(PyObject* in) {
  nose_position out;
  PyObject* i;
  i = PyTuple_GetItem(in, 0);
  if (i == NULL)
    throw 42;
  out.x = lang2cxx<PyObject*, int>(i);
  i = PyTuple_GetItem(in, 1);
  if (i == NULL)
    throw 42;
  out.y = lang2cxx<PyObject*, int>(i);
  return out;
}

/// Attack or Defend a position with a given amount of stock.
static PyObject* p_play_mur(PyObject* self, PyObject* args) {
  (void)self;
  PyObject* a0;
  PyObject* a1;
  if (!PyArg_ParseTuple(args, "OO", &a0, &a1)) {
    return NULL;
  }
  try {
    return cxx2lang<PyObject*, action_error>(api_play_mur(
        lang2cxx<PyObject*, mur_position>(a0), lang2cxx<PyObject*, int>(a1)));
  } catch (...) {
    return NULL;
  }
}

/// Remove squares with position >= to the given square.
static PyObject* p_play_nose(PyObject* self, PyObject* args) {
  (void)self;
  PyObject* a0;
  PyObject* a1;
  if (!PyArg_ParseTuple(args, "OO", &a0, &a1)) {
    return NULL;
  }
  try {
    return cxx2lang<PyObject*, action_error>(api_play_nose(
        lang2cxx<PyObject*, int>(a0), lang2cxx<PyObject*, int>(a1)));
  } catch (...) {
    return NULL;
  }
}

/// Your identifier (not always in {0, 1}).
static PyObject* p_me(PyObject* self, PyObject* args) {
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
  try {
    return cxx2lang<PyObject*, int>(api_me());
  } catch (...) {
    return NULL;
  }
}

/// Your opponent's identifier (not always in {0, 1}).
static PyObject* p_opponent(PyObject* self, PyObject* args) {
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
  try {
    return cxx2lang<PyObject*, int>(api_opponent());
  } catch (...) {
    return NULL;
  }
}

/// The current score of the specified player.
static PyObject* p_score(PyObject* self, PyObject* args) {
  (void)self;
  PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
  try {
    return cxx2lang<PyObject*, int>(api_score(lang2cxx<PyObject*, int>(a0)));
  } catch (...) {
    return NULL;
  }
}

/// MUR role (attacker/defender) of the specified player.
static PyObject* p_mur_role_of_player(PyObject* self, PyObject* args) {
  (void)self;
  PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
  try {
    return cxx2lang<PyObject*, mur_role>(
        api_mur_role_of_player(lang2cxx<PyObject*, int>(a0)));
  } catch (...) {
    return NULL;
  }
}

/// Current amount of stock remaining for the specified player.
static PyObject* p_mur_stock(PyObject* self, PyObject* args) {
  (void)self;
  PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
  try {
    return cxx2lang<PyObject*, int>(
        api_mur_stock(lang2cxx<PyObject*, int>(a0)));
  } catch (...) {
    return NULL;
  }
}

/// Amount of stock lost considering both players' moves.
static PyObject* p_mur_compute_stock_loss(PyObject* self, PyObject* args) {
  (void)self;
  PyObject* a0;
  PyObject* a1;
  PyObject* a2;
  PyObject* a3;
  if (!PyArg_ParseTuple(args, "OOOO", &a0, &a1, &a2, &a3)) {
    return NULL;
  }
  try {
    return cxx2lang<PyObject*, int>(api_mur_compute_stock_loss(
        lang2cxx<PyObject*, mur_position>(a0),
        lang2cxx<PyObject*, mur_position>(a1), lang2cxx<PyObject*, int>(a2),
        lang2cxx<PyObject*, int>(a3)));
  } catch (...) {
    return NULL;
  }
}

/// Last MUR position played by the specified player.
static PyObject* p_mur_last_pos(PyObject* self, PyObject* args) {
  (void)self;
  PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
  try {
    return cxx2lang<PyObject*, mur_position>(
        api_mur_last_pos(lang2cxx<PyObject*, int>(a0)));
  } catch (...) {
    return NULL;
  }
}

/// Last stock amount used by the specified player.
static PyObject* p_mur_last_used_stock(PyObject* self, PyObject* args) {
  (void)self;
  PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
  try {
    return cxx2lang<PyObject*, int>(
        api_mur_last_used_stock(lang2cxx<PyObject*, int>(a0)));
  } catch (...) {
    return NULL;
  }
}

/// Position of the last played square in the NOSE game.
static PyObject* p_nose_last_played_square(PyObject* self, PyObject* args) {
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
  try {
    return cxx2lang<PyObject*, nose_position>(api_nose_last_played_square());
  } catch (...) {
    return NULL;
  }
}

/// Number of remaining squares in the NOSE game.
static PyObject* p_nose_remaining_squares(PyObject* self, PyObject* args) {
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
  try {
    return cxx2lang<PyObject*, int>(api_nose_remaining_squares());
  } catch (...) {
    return NULL;
  }
}

/// Minimum number of squares to take. Returns -1 if the MUR game of the current
/// turn is not over.
static PyObject* p_nose_squares_to_take(PyObject* self, PyObject* args) {
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
  try {
    return cxx2lang<PyObject*, int>(api_nose_squares_to_take());
  } catch (...) {
    return NULL;
  }
}

/// count number of squares taken for a specific move
static PyObject* p_nose_squares_taken(PyObject* self, PyObject* args) {
  (void)self;
  PyObject* a0;
  PyObject* a1;
  if (!PyArg_ParseTuple(args, "OO", &a0, &a1)) {
    return NULL;
  }
  try {
    return cxx2lang<PyObject*, int>(api_nose_squares_taken(
        lang2cxx<PyObject*, int>(a0), lang2cxx<PyObject*, int>(a1)));
  } catch (...) {
    return NULL;
  }
}

/// Affiche le contenu d'une valeur de type mur_position
static PyObject* p_afficher_mur_position(PyObject* self, PyObject* args) {
  (void)self;
  PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
  try {
    api_afficher_mur_position(lang2cxx<PyObject*, mur_position>(a0));
    Py_INCREF(Py_None);
    return Py_None;
  } catch (...) {
    return NULL;
  }
}

/// Affiche le contenu d'une valeur de type mur_role
static PyObject* p_afficher_mur_role(PyObject* self, PyObject* args) {
  (void)self;
  PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
  try {
    api_afficher_mur_role(lang2cxx<PyObject*, mur_role>(a0));
    Py_INCREF(Py_None);
    return Py_None;
  } catch (...) {
    return NULL;
  }
}

/// Affiche le contenu d'une valeur de type action_error
static PyObject* p_afficher_action_error(PyObject* self, PyObject* args) {
  (void)self;
  PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
  try {
    api_afficher_action_error(lang2cxx<PyObject*, action_error>(a0));
    Py_INCREF(Py_None);
    return Py_None;
  } catch (...) {
    return NULL;
  }
}

/// Affiche le contenu d'une valeur de type nose_position
static PyObject* p_afficher_nose_position(PyObject* self, PyObject* args) {
  (void)self;
  PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
  try {
    api_afficher_nose_position(lang2cxx<PyObject*, nose_position>(a0));
    Py_INCREF(Py_None);
    return Py_None;
  } catch (...) {
    return NULL;
  }
}

/*
** Api functions to register.
*/
static PyMethodDef api_callback[] = {
    {"play_mur", p_play_mur, METH_VARARGS, "play_mur"},
    {"play_nose", p_play_nose, METH_VARARGS, "play_nose"},
    {"me", p_me, METH_VARARGS, "me"},
    {"opponent", p_opponent, METH_VARARGS, "opponent"},
    {"score", p_score, METH_VARARGS, "score"},
    {"mur_role_of_player", p_mur_role_of_player, METH_VARARGS,
     "mur_role_of_player"},
    {"mur_stock", p_mur_stock, METH_VARARGS, "mur_stock"},
    {"mur_compute_stock_loss", p_mur_compute_stock_loss, METH_VARARGS,
     "mur_compute_stock_loss"},
    {"mur_last_pos", p_mur_last_pos, METH_VARARGS, "mur_last_pos"},
    {"mur_last_used_stock", p_mur_last_used_stock, METH_VARARGS,
     "mur_last_used_stock"},
    {"nose_last_played_square", p_nose_last_played_square, METH_VARARGS,
     "nose_last_played_square"},
    {"nose_remaining_squares", p_nose_remaining_squares, METH_VARARGS,
     "nose_remaining_squares"},
    {"nose_squares_to_take", p_nose_squares_to_take, METH_VARARGS,
     "nose_squares_to_take"},
    {"nose_squares_taken", p_nose_squares_taken, METH_VARARGS,
     "nose_squares_taken"},
    {"afficher_mur_position", p_afficher_mur_position, METH_VARARGS,
     "afficher_mur_position"},
    {"afficher_mur_role", p_afficher_mur_role, METH_VARARGS,
     "afficher_mur_role"},
    {"afficher_action_error", p_afficher_action_error, METH_VARARGS,
     "afficher_action_error"},
    {"afficher_nose_position", p_afficher_nose_position, METH_VARARGS,
     "afficher_nose_position"},
    {NULL, NULL, 0, NULL}};

PyMODINIT_FUNC PyInit__api() {
  static struct PyModuleDef apimoduledef = {
      PyModuleDef_HEAD_INIT,
      "_api",
      "API module",
      -1,
      api_callback,
      NULL,
      NULL,
      NULL,
      NULL,
  };
  return PyModule_Create(&apimoduledef);
}

/*
** Load a Python module
*/

static PyObject* _import_module(const char* m) {
  PyObject* name = PyUnicode_FromString(m);
  PyObject* module = PyImport_Import(name);
  Py_DECREF(name);
  if (module == NULL)
    if (PyErr_Occurred()) {
      PyErr_Print();
      abort();
    }
  return module;
}

/*
** Inititialize python, register API functions,
** and load .py file
*/
static void _init_python() {
  static wchar_t empty_string[] = L"";
  static wchar_t* argv[] = {(wchar_t*)&empty_string, NULL};

  const char* champion_path;

  champion_path = getenv("CHAMPION_PATH");
  if (champion_path == NULL)
    champion_path = ".";

  setenv("PYTHONPATH", champion_path, 1);

  static wchar_t program_name[] = L"stechec";
  Py_SetProgramName(program_name);

  PyImport_AppendInittab("_api", PyInit__api);
  Py_Initialize();
  PySys_SetArgvEx(1, argv, 0);

  champ_module = _import_module("ai");
  py_module = _import_module("api");
}

/*
** Run a python function.
*/
static PyObject* _call_python_function(const char* name) {
  static bool initialized = false;

  if (!initialized) {
    initialized = true;
    _init_python();
  }

  PyObject *arglist, *func;
  PyObject* result = NULL;

  func = PyObject_GetAttrString(champ_module, (char*)name);
  if (func && PyCallable_Check(func)) {
    arglist = Py_BuildValue("()");
    result = PyEval_CallObject(func, arglist);
    Py_XDECREF(arglist);
    Py_DECREF(func);
  }
  if (result == NULL && PyErr_Occurred())
    PyErr_Print();

  return result;
}

/*
** Functions called from stechec to C.
*/
extern "C" void game_init() {
  PyObject* _retval = _call_python_function("game_init");
  if (!_retval && PyErr_Occurred()) {
    PyErr_Print();
    abort();
  }
  try {
    Py_XDECREF(_retval);
  } catch (...) {
    PyErr_Print();
    abort();
  }
}

extern "C" void mur_turn() {
  PyObject* _retval = _call_python_function("mur_turn");
  if (!_retval && PyErr_Occurred()) {
    PyErr_Print();
    abort();
  }
  try {
    Py_XDECREF(_retval);
  } catch (...) {
    PyErr_Print();
    abort();
  }
}

extern "C" void mur_end() {
  PyObject* _retval = _call_python_function("mur_end");
  if (!_retval && PyErr_Occurred()) {
    PyErr_Print();
    abort();
  }
  try {
    Py_XDECREF(_retval);
  } catch (...) {
    PyErr_Print();
    abort();
  }
}

extern "C" void nose_turn() {
  PyObject* _retval = _call_python_function("nose_turn");
  if (!_retval && PyErr_Occurred()) {
    PyErr_Print();
    abort();
  }
  try {
    Py_XDECREF(_retval);
  } catch (...) {
    PyErr_Print();
    abort();
  }
}

extern "C" void game_end() {
  PyObject* _retval = _call_python_function("game_end");
  if (!_retval && PyErr_Occurred()) {
    PyErr_Print();
    abort();
  }
  try {
    Py_XDECREF(_retval);
  } catch (...) {
    PyErr_Print();
    abort();
  }
}
