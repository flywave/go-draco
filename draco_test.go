package draco

import (
	"fmt"
	"io/ioutil"
	"testing"

	"github.com/flywave/go3d/vec2"
	"github.com/flywave/go3d/vec3"
)

func TestDecode_Error(t *testing.T) {
	m := NewMesh()
	d := NewDecoder()
	err := d.DecodeMesh(m, []byte{1, 2, 3})
	if err == nil {
		t.Fatal("Decode expecting error")
	}
	if err, ok := err.(*Error); ok {
		if err.Code != -2 {
			t.Errorf("Decode error want -2, got %v", err.Code)
		}
		want := "Failed to parse Draco header."
		if err.Message != want {
			t.Errorf("Decode error want %s, got %v", want, err.Message)
		}
	} else {
		t.Errorf("Decode error is not an *Error: %v", err)
	}
}

func TestDecode(t *testing.T) {
	data, err := ioutil.ReadFile("./testdata/test_nm.obj.edgebreaker.cl4.2.2.drc")
	if err != nil {
		t.Fatalf("failed to read test file: %v", err)
	}
	if got := GetEncodedGeometryType(data); got != EGT_TRIANGULAR_MESH {
		t.Errorf("GetEncodedGeometryType want EGT_TRIANGULAR_MESH, got %v", got)
	}
	m := NewMesh()
	d := NewDecoder()
	if err := d.DecodeMesh(m, data); err != nil {
		t.Fatalf("failed to decode mesh: %v", err)
	}
	if n := m.NumFaces(); n != 170 {
		t.Errorf("Mesh.NumFaces want 170, got %d", n)
	}
	if n := m.NumPoints(); n != 99 {
		t.Errorf("Mesh.NumFaces want 99, got %d", n)
	}
	if n := m.NumAttrs(); n != 2 {
		t.Errorf("Mesh.NumFaces want 2, got %d", n)
	}
	faces := m.Faces(nil)
	want := []uint32{0, 1, 2}
	if got := faces[2]; got != want[2] {
		t.Errorf("Mesh.Faces[0] want %v, got %v", want, got)
	}
	for i := int32(0); i < m.NumAttrs(); i++ {
		attr := m.Attr(i)
		if got := attr.Type(); got == GAT_INVALID {
			t.Error("PointAttr.Type got GT_INVALID")
		}
		if m.NamedAttributeID(attr.Type()) != i {
			t.Error("PointAttr.Type and Mesh.NamedAttributeID mismatch")
		}
		if got := attr.DataType(); got == DT_INVALID {
			t.Error("PointAttr.DataType got DT_INVALID")
		}
		if got := attr.NumComponents(); got == 0 {
			t.Error("PointAttr.NumComponents got 0")
		}
		if got := attr.Normalized(); got {
			t.Error("PointAttr.Normalized got true")
		}
		if got := attr.ByteStride(); got == 0 {
			t.Error("PointAttr.ByteStride got 0")
		}
		if got := attr.UniqueID(); got != uint32(i) {
			t.Errorf("PointAttr.UniqueID got %d, want %d", got, i)
		}
	}
	attr1 := m.AttrByUniqueID(0)
	if _, ok := m.AttrData(attr1, nil); !ok {
		t.Error("Mesh.AttrData failed")
	}
	if _, ok := m.AttrData(attr1, []float64{}); !ok {
		t.Error("Mesh.AttrData failed")
	}
	if _, ok := m.AttrData(attr1, []float32{1, 2, 3}); !ok {
		t.Error("Mesh.AttrData failed")
	}
	if _, ok := m.AttrData(attr1, []int32{1, 2, 3}); !ok {
		t.Error("Mesh.AttrData failed")
	}
	if _, ok := m.AttrData(attr1, make([]float64, 1000)); !ok {
		t.Error("Mesh.AttrData failed")
	}
}

var (
	Verts = []vec3.T{
		{0., 0., 0.},
		{1., 0., 0.},
		{0., 1., 0.},
		{0., 1., 0.},
		{1., 0., 0.},
		{1., 1., 0.},
		{0., 1., 1.},
		{1., 0., 1.},
		{0., 0., 1.},
		{1., 1., 1.},
		{1., 0., 1.},
		{0., 1., 1.},
		{0., 1., 0.},
		{1., 1., 0.},
		{0., 1., 1.},
		{0., 1., 1.},
		{1., 1., 0.},
		{1., 1., 1.},
		{0., 0., 1.},
		{1., 0., 0.},
		{0., 0., 0.},
		{1., 0., 1.},
		{1., 0., 0.},
		{0., 0., 1.},
		{1., 0., 0.},
		{1., 0., 1.},
		{1., 1., 0.},
		{1., 1., 0.},
		{1., 0., 1.},
		{1., 1., 1.},
		{0., 1., 0.},
		{0., 0., 1.},
		{0., 0., 0.},
		{0., 1., 1.},
		{0., 0., 1.},
		{0., 1., 0.}}
	Faces = [][3]uint16{
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8},
		{9, 10, 11},
		{12, 13, 14},
		{15, 16, 17},
		{18, 19, 20},
		{21, 22, 23},
		{24, 25, 26},
		{27, 28, 29},
		{30, 31, 32},
		{33, 34, 35},
	}
	Texcoords = []vec2.T{
		{0, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
		{0.5, 0.5},
	}
)

func TestEncoderDecoder(t *testing.T) {
	enc := NewEncoder()
	builder := NewMeshBuilder()
	size := len(Faces)

	builder.Start(size)

	builder.SetAttribute(size, Verts[:], GAT_POSITION)
	builder.SetAttribute(size, Texcoords[:], GAT_TEX_COORD)

	mesh := builder.GetMesh()
	_, buf := enc.EncodeMesh(mesh)

	if len(buf) == 0 {
		t.FailNow()
	}

	denc := NewDecoder()
	outmesh := NewMesh()

	err := denc.DecodeMesh(outmesh, buf)

	if err != nil {
		t.FailNow()
	}
	var facecount int
	if facecount = int(outmesh.NumFaces()); facecount != len(Faces) {
		t.FailNow()
	}

	outface := make([]uint32, facecount*3)
	outface = outmesh.Faces(outface)

	vertcount := outmesh.NumPoints()
	outvert := make([]float32, vertcount*3)

	posid := outmesh.NamedAttributeID(GAT_POSITION)
	outmesh.AttrData(outmesh.Attr(posid), outvert)

	for f := 0; f < facecount; f++ {
		for i := 0; i < 3; i++ {
			fmt.Printf("[%f, %f, %f]", outvert[outface[f*3+i]*3], outvert[outface[f*3+i]*3+1], outvert[outface[f*3+i]*3+2])
		}
	}
}
