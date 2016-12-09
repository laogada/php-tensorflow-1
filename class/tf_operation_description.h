// // Operation being built. The underlying graph must outlive this.
// typedef struct TF_OperationDescription TF_OperationDescription;

// // Specify the device for `desc`.  Defaults to empty, meaning unconstrained.
// extern void TF_SetDevice(TF_OperationDescription* desc, const char* device);

// // Operation will only be added to *graph when TF_FinishOperation() is
// // called (assuming TF_FinishOperation() does not return an error).
// // *graph must not be deleted until after TF_FinishOperation() is
// // called.
// extern TF_OperationDescription* TF_NewOperation(TF_Graph* graph,
//                                                 const char* op_type,
//                                                 const char* oper_name);

// // The calls to TF_AddInput and TF_AddInputList must match (in number,
// // order, and type) the op declaration.  For example, the "Concat" op
// // has registration:
// //   REGISTER_OP("Concat")
// //       .Input("concat_dim: int32")
// //       .Input("values: N * T")
// //       .Output("output: T")
// //       .Attr("N: int >= 2")
// //       .Attr("T: type");
// // that defines two inputs, "concat_dim" and "values" (in that order).
// // You must use TF_AddInput() for the first input (since it takes a
// // single tensor), and TF_AddInputList() for the second input (since
// // it takes a list, even if you were to pass a list with a single
// // tensor), as in:
// //   TF_OperationDescription* desc = TF_NewOperation(graph, "Concat", "c");
// //   TF_Output concat_dim_input = {...};
// //   TF_AddInput(desc, concat_dim_input);
// //   TF_Output values_inputs[5] = {{...}, ..., {...}};
// //   TF_AddInputList(desc, values_inputs, 5);

// // For inputs that take a single tensor.
// extern void TF_AddInput(TF_OperationDescription* desc, TF_Output input);

// // For inputs that take a list of tensors.
// // inputs must point to TF_Output[num_inputs].
// extern void TF_AddInputList(TF_OperationDescription* desc,
//                             const TF_Output* inputs, int num_inputs);

// // Call once per control input to `desc`.
// extern void TF_AddControlInput(TF_OperationDescription* desc,
//                                TF_Operation* input);

// // Request that `desc` be co-located on the device where `op`
// // is placed.
// //
// // Use of this is discouraged since the implementation of device placement is
// // subject to change. Primarily intended for internal libraries
// extern void TF_ColocateWith(TF_OperationDescription* desc, TF_Operation* op);

// // Call some TF_SetAttr*() function for every attr that is not
// // inferred from an input and doesn't have a default value you wish to
// // keep.

// // `value` must point to a string of length `length` bytes.
// extern void TF_SetAttrString(TF_OperationDescription* desc,
//                              const char* attr_name, const void* value,
//                              size_t length);
// // `values` and `lengths` each must have lengths `num_values`.
// // `values[i]` must point to a string of length `lengths[i]` bytes.
// extern void TF_SetAttrStringList(TF_OperationDescription* desc,
//                                  const char* attr_name,
//                                  const void* const* values,
//                                  const size_t* lengths, int num_values);
// extern void TF_SetAttrInt(TF_OperationDescription* desc, const char* attr_name,
//                           int64_t value);
// extern void TF_SetAttrIntList(TF_OperationDescription* desc,
//                               const char* attr_name, const int64_t* values,
//                               int num_values);
// extern void TF_SetAttrFloat(TF_OperationDescription* desc,
//                             const char* attr_name, float value);
// extern void TF_SetAttrFloatList(TF_OperationDescription* desc,
//                                 const char* attr_name, const float* values,
//                                 int num_values);
// extern void TF_SetAttrBool(TF_OperationDescription* desc, const char* attr_name,
//                            unsigned char value);
// extern void TF_SetAttrBoolList(TF_OperationDescription* desc,
//                                const char* attr_name,
//                                const unsigned char* values, int num_values);
// extern void TF_SetAttrType(TF_OperationDescription* desc, const char* attr_name,
//                            TF_DataType value);
// extern void TF_SetAttrTypeList(TF_OperationDescription* desc,
//                                const char* attr_name, const TF_DataType* values,
//                                int num_values);

// // Set `num_dims` to -1 to represent "unknown rank".  Otherwise,
// // `dims` points to an array of length `num_dims`.  `dims[i]` must be
// // >= -1, with -1 meaning "unknown dimension".
// extern void TF_SetAttrShape(TF_OperationDescription* desc,
//                             const char* attr_name, const int64_t* dims,
//                             int num_dims);
// // `dims` and `num_dims` must point to arrays of length `num_shapes`.
// // Set `num_dims[i]` to -1 to represent "unknown rank".  Otherwise,
// // `dims[i]` points to an array of length `num_dims[i]`.  `dims[i][j]`
// // must be >= -1, with -1 meaning "unknown dimension".
// extern void TF_SetAttrShapeList(TF_OperationDescription* desc,
//                                 const char* attr_name,
//                                 const int64_t* const* dims, const int* num_dims,
//                                 int num_shapes);
// // `proto` must point to an array of `proto_len` bytes representing a
// // binary-serialized TensorShapeProto.
// extern void TF_SetAttrTensorShapeProto(TF_OperationDescription* desc,
//                                        const char* attr_name, const void* proto,
//                                        size_t proto_len, TF_Status* status);
// // `protos` and `proto_lens` must point to arrays of length `num_shapes`.
// // `protos[i]` must point to an array of `proto_lens[i]` bytes
// // representing a binary-serialized TensorShapeProto.
// extern void TF_SetAttrTensorShapeProtoList(TF_OperationDescription* desc,
//                                            const char* attr_name,
//                                            const void* const* protos,
//                                            const size_t* proto_lens,
//                                            int num_shapes, TF_Status* status);

// extern void TF_SetAttrTensor(TF_OperationDescription* desc,
//                              const char* attr_name, TF_Tensor* value,
//                              TF_Status* status);
// extern void TF_SetAttrTensorList(TF_OperationDescription* desc,
//                                  const char* attr_name,
//                                  TF_Tensor* const* values, int num_values,
//                                  TF_Status* status);

// // `proto` should point to a sequence of bytes of length `proto_len`
// // representing a binary serialization of an AttrValue protocol
// // buffer.
// extern void TF_SetAttrValueProto(TF_OperationDescription* desc,
//                                  const char* attr_name, const void* proto,
//                                  size_t proto_len, TF_Status* status);

// // If this function succeeds:
// //   * *status is set to an OK value,
// //   * a TF_Operation is added to the graph,
// //   * a non-null value pointing to the added operation is returned --
// //     this value is valid until the underlying graph is deleted.
// // Otherwise:
// //   * *status is set to a non-OK value,
// //   * the graph is not modified,
// //   * a null value is returned.
// // In either case, it deletes `desc`.
// extern TF_Operation* TF_FinishOperation(TF_OperationDescription* desc,
//                                         TF_Status* status);
