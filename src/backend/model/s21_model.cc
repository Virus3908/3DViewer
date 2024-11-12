#include "s21_model.h"

namespace s21 {

Model &Model::getModel() {
  static Model instance;
  return instance;
}

void Model::clearModel() {
  vertices.clear();
  faces.clear();
  edges.clear();
}

Status_e Model::readFile(const std::string &FileName) {
  Status_e status = Status_e::OK;
  clearModel();
  std::ifstream file(FileName);
  if (!file.is_open()) {
    status = Status_e::ReadError;
  } else {
    std::string line;
    while (status == Status_e::OK && std::getline(file, line)) {
      status = readLine(line);
    }
    status = (vertices.empty() || faces.empty()) && status == Status_e::OK
                 ? EmptyFile
                 : status;
    if (status != Status_e::OK) {
      clearModel();
    }
    file.close();
  }
  return status;
}

Status_e Model::readLine(std::string line) {
  std::istringstream iss(line);
  Status_e status = Status_e::OK;
  std::string type;
  iss >> type;
  if (type == "v") {
    status = pushVertex(iss);
  } else if (type == "f") {
    status = pushFace(iss);
  }
  return status;
}

Status_e Model::pushVertex(std::istringstream &iss) {
  Vertex_t vertex;
  Status_e status = Status_e::OK;
  if (iss >> vertex.x >> vertex.y >> vertex.z) {
    vertices.push_back(vertex);
  } else {
    status = Status_e::FileCurrupted;
  }
  return status;
}

Status_e Model::pushFace(std::istringstream &iss) {
  Face_t face;
  Status_e status = Status_e::OK;
  std::string vertexData;
  while (iss >> vertexData && status == Status_e::OK) {
    std::istringstream vertexStream(vertexData);
    std::string vertIndex;
    std::getline(vertexStream, vertIndex, '/');
    try {
      long ind = std::stoi(vertIndex);
      if (ind < 0) {
        ind += vertices.size();
      } else {
        ind -= 1;
      }
      face.vertexIndex.push_back(unsigned(ind));
      if (ind > long(vertices.size())) {
        status = Status_e::FileCurrupted;
      }
    } catch (const std::out_of_range &e) {
      status = Status_e::FileCurrupted;
    }
  }
  if (face.vertexIndex.size() < 3) {
    status = Status_e::FileCurrupted;
  }
  if (status == Status_e::OK) {
    faces.push_back(face);
    getEdgeFromFace(face);
  }
  return status;
}

void Model::getEdgeFromFace(const Face_t &face) {
  unsigned size = face.vertexIndex.size();
  for (unsigned i = 0; i < size; ++i) {
    edges.push_back(
        Edge_t(face.vertexIndex[i], face.vertexIndex[(i + 1) % size]));
  }
}

const std::vector<Vertex_t> &Model::getVertex() { return vertices; }

const std::vector<Face_t> &Model::getFace() { return faces; }

const std::vector<Edge_t> &Model::getEdge() { return edges; }

}  // namespace s21