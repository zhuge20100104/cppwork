üå
¦÷
B
AssignVariableOp
resource
value"dtype"
dtypetype
~
BiasAdd

value"T	
bias"T
output"T" 
Ttype:
2	"-
data_formatstringNHWC:
NHWCNCHW
8
Const
output"dtype"
valuetensor"
dtypetype
.
Identity

input"T
output"T"	
Ttype
q
MatMul
a"T
b"T
product"T"
transpose_abool( "
transpose_bbool( "
Ttype:

2	
e
MergeV2Checkpoints
checkpoint_prefixes
destination_prefix"
delete_old_dirsbool(

NoOp
M
Pack
values"T*N
output"T"
Nint(0"	
Ttype"
axisint 
C
Placeholder
output"dtype"
dtypetype"
shapeshape:
@
ReadVariableOp
resource
value"dtype"
dtypetype
o
	RestoreV2

prefix
tensor_names
shape_and_slices
tensors2dtypes"
dtypes
list(type)(0
l
SaveV2

prefix
tensor_names
shape_and_slices
tensors2dtypes"
dtypes
list(type)(0
?
Select
	condition

t"T
e"T
output"T"	
Ttype
H
ShardedFilename
basename	
shard

num_shards
filename
9
Softmax
logits"T
softmax"T"
Ttype:
2
¾
StatefulPartitionedCall
args2Tin
output2Tout"
Tin
list(type)("
Tout
list(type)("	
ffunc"
configstring "
config_protostring "
executor_typestring 
@
StaticRegexFullMatch	
input

output
"
patternstring
N

StringJoin
inputs*N

output"
Nint(0"
	separatorstring 

VarHandleOp
resource"
	containerstring "
shared_namestring "
dtypetype"
shapeshape"#
allowed_deviceslist(string)
 "serve*2.6.02v2.6.0-rc2-32-g919f693420e8¬

iris_model/input_iris/kernelVarHandleOp*
_output_shapes
: *
dtype0*
shape
:*-
shared_nameiris_model/input_iris/kernel

0iris_model/input_iris/kernel/Read/ReadVariableOpReadVariableOpiris_model/input_iris/kernel*
_output_shapes

:*
dtype0

iris_model/input_iris/biasVarHandleOp*
_output_shapes
: *
dtype0*
shape:*+
shared_nameiris_model/input_iris/bias

.iris_model/input_iris/bias/Read/ReadVariableOpReadVariableOpiris_model/input_iris/bias*
_output_shapes
:*
dtype0
d
SGD/iterVarHandleOp*
_output_shapes
: *
dtype0	*
shape: *
shared_name
SGD/iter
]
SGD/iter/Read/ReadVariableOpReadVariableOpSGD/iter*
_output_shapes
: *
dtype0	
f
	SGD/decayVarHandleOp*
_output_shapes
: *
dtype0*
shape: *
shared_name	SGD/decay
_
SGD/decay/Read/ReadVariableOpReadVariableOp	SGD/decay*
_output_shapes
: *
dtype0
v
SGD/learning_rateVarHandleOp*
_output_shapes
: *
dtype0*
shape: *"
shared_nameSGD/learning_rate
o
%SGD/learning_rate/Read/ReadVariableOpReadVariableOpSGD/learning_rate*
_output_shapes
: *
dtype0
l
SGD/momentumVarHandleOp*
_output_shapes
: *
dtype0*
shape: *
shared_nameSGD/momentum
e
 SGD/momentum/Read/ReadVariableOpReadVariableOpSGD/momentum*
_output_shapes
: *
dtype0
^
totalVarHandleOp*
_output_shapes
: *
dtype0*
shape: *
shared_nametotal
W
total/Read/ReadVariableOpReadVariableOptotal*
_output_shapes
: *
dtype0
^
countVarHandleOp*
_output_shapes
: *
dtype0*
shape: *
shared_namecount
W
count/Read/ReadVariableOpReadVariableOpcount*
_output_shapes
: *
dtype0
b
total_1VarHandleOp*
_output_shapes
: *
dtype0*
shape: *
shared_name	total_1
[
total_1/Read/ReadVariableOpReadVariableOptotal_1*
_output_shapes
: *
dtype0
b
count_1VarHandleOp*
_output_shapes
: *
dtype0*
shape: *
shared_name	count_1
[
count_1/Read/ReadVariableOpReadVariableOpcount_1*
_output_shapes
: *
dtype0

NoOpNoOp
¹
ConstConst"/device:CPU:0*
_output_shapes
: *
dtype0*ô
valueêBç Bà
y
d1
	optimizer
regularization_losses
	variables
trainable_variables
	keras_api

signatures
h

kernel
	bias

regularization_losses
	variables
trainable_variables
	keras_api
6
iter
	decay
learning_rate
momentum
 

0
	1

0
	1
­
regularization_losses
layer_metrics
	variables
non_trainable_variables
metrics
layer_regularization_losses

layers
trainable_variables
 
VT
VARIABLE_VALUEiris_model/input_iris/kernel$d1/kernel/.ATTRIBUTES/VARIABLE_VALUE
RP
VARIABLE_VALUEiris_model/input_iris/bias"d1/bias/.ATTRIBUTES/VARIABLE_VALUE
 

0
	1

0
	1
­

regularization_losses
layer_metrics
	variables
non_trainable_variables
metrics
layer_regularization_losses

layers
trainable_variables
GE
VARIABLE_VALUESGD/iter)optimizer/iter/.ATTRIBUTES/VARIABLE_VALUE
IG
VARIABLE_VALUE	SGD/decay*optimizer/decay/.ATTRIBUTES/VARIABLE_VALUE
YW
VARIABLE_VALUESGD/learning_rate2optimizer/learning_rate/.ATTRIBUTES/VARIABLE_VALUE
OM
VARIABLE_VALUESGD/momentum-optimizer/momentum/.ATTRIBUTES/VARIABLE_VALUE
 
 

0
1
 

0
 
 
 
 
 
4
	total
	count
 	variables
!	keras_api
D
	"total
	#count
$
_fn_kwargs
%	variables
&	keras_api
OM
VARIABLE_VALUEtotal4keras_api/metrics/0/total/.ATTRIBUTES/VARIABLE_VALUE
OM
VARIABLE_VALUEcount4keras_api/metrics/0/count/.ATTRIBUTES/VARIABLE_VALUE

0
1

 	variables
QO
VARIABLE_VALUEtotal_14keras_api/metrics/1/total/.ATTRIBUTES/VARIABLE_VALUE
QO
VARIABLE_VALUEcount_14keras_api/metrics/1/count/.ATTRIBUTES/VARIABLE_VALUE
 

"0
#1

%	variables
z
serving_default_input_1Placeholder*'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ*
dtype0*
shape:ÿÿÿÿÿÿÿÿÿ
ð
StatefulPartitionedCallStatefulPartitionedCallserving_default_input_1iris_model/input_iris/kerneliris_model/input_iris/bias*
Tin
2*
Tout
2*
_collective_manager_ids
 *'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ*$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8 *-
f(R&
$__inference_signature_wrapper_125176
O
saver_filenamePlaceholder*
_output_shapes
: *
dtype0*
shape: 
ý
StatefulPartitionedCall_1StatefulPartitionedCallsaver_filename0iris_model/input_iris/kernel/Read/ReadVariableOp.iris_model/input_iris/bias/Read/ReadVariableOpSGD/iter/Read/ReadVariableOpSGD/decay/Read/ReadVariableOp%SGD/learning_rate/Read/ReadVariableOp SGD/momentum/Read/ReadVariableOptotal/Read/ReadVariableOpcount/Read/ReadVariableOptotal_1/Read/ReadVariableOpcount_1/Read/ReadVariableOpConst*
Tin
2	*
Tout
2*
_collective_manager_ids
 *
_output_shapes
: * 
_read_only_resource_inputs
 *-
config_proto

CPU

GPU 2J 8 *(
f#R!
__inference__traced_save_125298
°
StatefulPartitionedCall_2StatefulPartitionedCallsaver_filenameiris_model/input_iris/kerneliris_model/input_iris/biasSGD/iter	SGD/decaySGD/learning_rateSGD/momentumtotalcounttotal_1count_1*
Tin
2*
Tout
2*
_collective_manager_ids
 *
_output_shapes
: * 
_read_only_resource_inputs
 *-
config_proto

CPU

GPU 2J 8 *+
f&R$
"__inference__traced_restore_125338»ÿ
æ

+__inference_iris_model_layer_call_fn_125202
x
unknown:
	unknown_0:
identity¢StatefulPartitionedCallñ
StatefulPartitionedCallStatefulPartitionedCallxunknown	unknown_0*
Tin
2*
Tout
2*
_collective_manager_ids
 *'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ*$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8 *O
fJRH
F__inference_iris_model_layer_call_and_return_conditional_losses_1251142
StatefulPartitionedCall{
IdentityIdentity StatefulPartitionedCall:output:0^NoOp*
T0*'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ2

Identityh
NoOpNoOp^StatefulPartitionedCall*"
_acd_function_control_output(*
_output_shapes
 2
NoOp"
identityIdentity:output:0*(
_construction_contextkEagerRuntime**
_input_shapes
:ÿÿÿÿÿÿÿÿÿ: : 22
StatefulPartitionedCallStatefulPartitionedCall:J F
'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ

_user_specified_namex


F__inference_iris_model_layer_call_and_return_conditional_losses_125155
input_1#
input_iris_125143:
input_iris_125145:
identity¢"input_iris/StatefulPartitionedCall¢>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp
"input_iris/StatefulPartitionedCallStatefulPartitionedCallinput_1input_iris_125143input_iris_125145*
Tin
2*
Tout
2*
_collective_manager_ids
 *'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ*$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8 *O
fJRH
F__inference_input_iris_layer_call_and_return_conditional_losses_1251012$
"input_iris/StatefulPartitionedCallÒ
>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOpReadVariableOpinput_iris_125143*
_output_shapes

:*
dtype02@
>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOpÝ
/iris_model/input_iris/kernel/Regularizer/SquareSquareFiris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp:value:0*
T0*
_output_shapes

:21
/iris_model/input_iris/kernel/Regularizer/Square±
.iris_model/input_iris/kernel/Regularizer/ConstConst*
_output_shapes
:*
dtype0*
valueB"       20
.iris_model/input_iris/kernel/Regularizer/Constò
,iris_model/input_iris/kernel/Regularizer/SumSum3iris_model/input_iris/kernel/Regularizer/Square:y:07iris_model/input_iris/kernel/Regularizer/Const:output:0*
T0*
_output_shapes
: 2.
,iris_model/input_iris/kernel/Regularizer/Sum¥
.iris_model/input_iris/kernel/Regularizer/mul/xConst*
_output_shapes
: *
dtype0*
valueB
 *
×#<20
.iris_model/input_iris/kernel/Regularizer/mul/xô
,iris_model/input_iris/kernel/Regularizer/mulMul7iris_model/input_iris/kernel/Regularizer/mul/x:output:05iris_model/input_iris/kernel/Regularizer/Sum:output:0*
T0*
_output_shapes
: 2.
,iris_model/input_iris/kernel/Regularizer/mul
IdentityIdentity+input_iris/StatefulPartitionedCall:output:0^NoOp*
T0*'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ2

Identity´
NoOpNoOp#^input_iris/StatefulPartitionedCall?^iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp*"
_acd_function_control_output(*
_output_shapes
 2
NoOp"
identityIdentity:output:0*(
_construction_contextkEagerRuntime**
_input_shapes
:ÿÿÿÿÿÿÿÿÿ: : 2H
"input_iris/StatefulPartitionedCall"input_iris/StatefulPartitionedCall2
>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp:P L
'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ
!
_user_specified_name	input_1
Ì

$__inference_signature_wrapper_125176
input_1
unknown:
	unknown_0:
identity¢StatefulPartitionedCallÒ
StatefulPartitionedCallStatefulPartitionedCallinput_1unknown	unknown_0*
Tin
2*
Tout
2*
_collective_manager_ids
 *'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ*$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8 **
f%R#
!__inference__wrapped_model_1250772
StatefulPartitionedCall{
IdentityIdentity StatefulPartitionedCall:output:0^NoOp*
T0*'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ2

Identityh
NoOpNoOp^StatefulPartitionedCall*"
_acd_function_control_output(*
_output_shapes
 2
NoOp"
identityIdentity:output:0*(
_construction_contextkEagerRuntime**
_input_shapes
:ÿÿÿÿÿÿÿÿÿ: : 22
StatefulPartitionedCallStatefulPartitionedCall:P L
'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ
!
_user_specified_name	input_1
ò
Ë
__inference_loss_fn_0_125245Y
Giris_model_input_iris_kernel_regularizer_square_readvariableop_resource:
identity¢>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp
>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOpReadVariableOpGiris_model_input_iris_kernel_regularizer_square_readvariableop_resource*
_output_shapes

:*
dtype02@
>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOpÝ
/iris_model/input_iris/kernel/Regularizer/SquareSquareFiris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp:value:0*
T0*
_output_shapes

:21
/iris_model/input_iris/kernel/Regularizer/Square±
.iris_model/input_iris/kernel/Regularizer/ConstConst*
_output_shapes
:*
dtype0*
valueB"       20
.iris_model/input_iris/kernel/Regularizer/Constò
,iris_model/input_iris/kernel/Regularizer/SumSum3iris_model/input_iris/kernel/Regularizer/Square:y:07iris_model/input_iris/kernel/Regularizer/Const:output:0*
T0*
_output_shapes
: 2.
,iris_model/input_iris/kernel/Regularizer/Sum¥
.iris_model/input_iris/kernel/Regularizer/mul/xConst*
_output_shapes
: *
dtype0*
valueB
 *
×#<20
.iris_model/input_iris/kernel/Regularizer/mul/xô
,iris_model/input_iris/kernel/Regularizer/mulMul7iris_model/input_iris/kernel/Regularizer/mul/x:output:05iris_model/input_iris/kernel/Regularizer/Sum:output:0*
T0*
_output_shapes
: 2.
,iris_model/input_iris/kernel/Regularizer/mulz
IdentityIdentity0iris_model/input_iris/kernel/Regularizer/mul:z:0^NoOp*
T0*
_output_shapes
: 2

Identity
NoOpNoOp?^iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp*"
_acd_function_control_output(*
_output_shapes
 2
NoOp"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*
_input_shapes
: 2
>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp
æ 
²
__inference__traced_save_125298
file_prefix;
7savev2_iris_model_input_iris_kernel_read_readvariableop9
5savev2_iris_model_input_iris_bias_read_readvariableop'
#savev2_sgd_iter_read_readvariableop	(
$savev2_sgd_decay_read_readvariableop0
,savev2_sgd_learning_rate_read_readvariableop+
'savev2_sgd_momentum_read_readvariableop$
 savev2_total_read_readvariableop$
 savev2_count_read_readvariableop&
"savev2_total_1_read_readvariableop&
"savev2_count_1_read_readvariableop
savev2_const

identity_1¢MergeV2Checkpoints
StaticRegexFullMatchStaticRegexFullMatchfile_prefix"/device:CPU:**
_output_shapes
: *
pattern
^s3://.*2
StaticRegexFullMatchc
ConstConst"/device:CPU:**
_output_shapes
: *
dtype0*
valueB B.part2
Constl
Const_1Const"/device:CPU:**
_output_shapes
: *
dtype0*
valueB B
_temp/part2	
Const_1
SelectSelectStaticRegexFullMatch:output:0Const:output:0Const_1:output:0"/device:CPU:**
T0*
_output_shapes
: 2
Selectt

StringJoin
StringJoinfile_prefixSelect:output:0"/device:CPU:**
N*
_output_shapes
: 2

StringJoinZ

num_shardsConst*
_output_shapes
: *
dtype0*
value	B :2

num_shards
ShardedFilename/shardConst"/device:CPU:0*
_output_shapes
: *
dtype0*
value	B : 2
ShardedFilename/shard¦
ShardedFilenameShardedFilenameStringJoin:output:0ShardedFilename/shard:output:0num_shards:output:0"/device:CPU:0*
_output_shapes
: 2
ShardedFilenameý
SaveV2/tensor_namesConst"/device:CPU:0*
_output_shapes
:*
dtype0*
valueBB$d1/kernel/.ATTRIBUTES/VARIABLE_VALUEB"d1/bias/.ATTRIBUTES/VARIABLE_VALUEB)optimizer/iter/.ATTRIBUTES/VARIABLE_VALUEB*optimizer/decay/.ATTRIBUTES/VARIABLE_VALUEB2optimizer/learning_rate/.ATTRIBUTES/VARIABLE_VALUEB-optimizer/momentum/.ATTRIBUTES/VARIABLE_VALUEB4keras_api/metrics/0/total/.ATTRIBUTES/VARIABLE_VALUEB4keras_api/metrics/0/count/.ATTRIBUTES/VARIABLE_VALUEB4keras_api/metrics/1/total/.ATTRIBUTES/VARIABLE_VALUEB4keras_api/metrics/1/count/.ATTRIBUTES/VARIABLE_VALUEB_CHECKPOINTABLE_OBJECT_GRAPH2
SaveV2/tensor_names
SaveV2/shape_and_slicesConst"/device:CPU:0*
_output_shapes
:*
dtype0*)
value BB B B B B B B B B B B 2
SaveV2/shape_and_slicesâ
SaveV2SaveV2ShardedFilename:filename:0SaveV2/tensor_names:output:0 SaveV2/shape_and_slices:output:07savev2_iris_model_input_iris_kernel_read_readvariableop5savev2_iris_model_input_iris_bias_read_readvariableop#savev2_sgd_iter_read_readvariableop$savev2_sgd_decay_read_readvariableop,savev2_sgd_learning_rate_read_readvariableop'savev2_sgd_momentum_read_readvariableop savev2_total_read_readvariableop savev2_count_read_readvariableop"savev2_total_1_read_readvariableop"savev2_count_1_read_readvariableopsavev2_const"/device:CPU:0*
_output_shapes
 *
dtypes
2	2
SaveV2º
&MergeV2Checkpoints/checkpoint_prefixesPackShardedFilename:filename:0^SaveV2"/device:CPU:0*
N*
T0*
_output_shapes
:2(
&MergeV2Checkpoints/checkpoint_prefixes¡
MergeV2CheckpointsMergeV2Checkpoints/MergeV2Checkpoints/checkpoint_prefixes:output:0file_prefix"/device:CPU:0*
_output_shapes
 2
MergeV2Checkpointsr
IdentityIdentityfile_prefix^MergeV2Checkpoints"/device:CPU:0*
T0*
_output_shapes
: 2

Identity_

Identity_1IdentityIdentity:output:0^NoOp*
T0*
_output_shapes
: 2

Identity_1c
NoOpNoOp^MergeV2Checkpoints*"
_acd_function_control_output(*
_output_shapes
 2
NoOp"!

identity_1Identity_1:output:0*7
_input_shapes&
$: ::: : : : : : : : : 2(
MergeV2CheckpointsMergeV2Checkpoints:C ?

_output_shapes
: 
%
_user_specified_namefile_prefix:$ 

_output_shapes

:: 

_output_shapes
::

_output_shapes
: :

_output_shapes
: :

_output_shapes
: :

_output_shapes
: :

_output_shapes
: :

_output_shapes
: :	

_output_shapes
: :


_output_shapes
: :

_output_shapes
: 

¸
F__inference_input_iris_layer_call_and_return_conditional_losses_125101

inputs0
matmul_readvariableop_resource:-
biasadd_readvariableop_resource:
identity¢BiasAdd/ReadVariableOp¢MatMul/ReadVariableOp¢>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp
MatMul/ReadVariableOpReadVariableOpmatmul_readvariableop_resource*
_output_shapes

:*
dtype02
MatMul/ReadVariableOps
MatMulMatMulinputsMatMul/ReadVariableOp:value:0*
T0*'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ2
MatMul
BiasAdd/ReadVariableOpReadVariableOpbiasadd_readvariableop_resource*
_output_shapes
:*
dtype02
BiasAdd/ReadVariableOp
BiasAddBiasAddMatMul:product:0BiasAdd/ReadVariableOp:value:0*
T0*'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ2	
BiasAdda
SoftmaxSoftmaxBiasAdd:output:0*
T0*'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ2	
Softmaxß
>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOpReadVariableOpmatmul_readvariableop_resource*
_output_shapes

:*
dtype02@
>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOpÝ
/iris_model/input_iris/kernel/Regularizer/SquareSquareFiris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp:value:0*
T0*
_output_shapes

:21
/iris_model/input_iris/kernel/Regularizer/Square±
.iris_model/input_iris/kernel/Regularizer/ConstConst*
_output_shapes
:*
dtype0*
valueB"       20
.iris_model/input_iris/kernel/Regularizer/Constò
,iris_model/input_iris/kernel/Regularizer/SumSum3iris_model/input_iris/kernel/Regularizer/Square:y:07iris_model/input_iris/kernel/Regularizer/Const:output:0*
T0*
_output_shapes
: 2.
,iris_model/input_iris/kernel/Regularizer/Sum¥
.iris_model/input_iris/kernel/Regularizer/mul/xConst*
_output_shapes
: *
dtype0*
valueB
 *
×#<20
.iris_model/input_iris/kernel/Regularizer/mul/xô
,iris_model/input_iris/kernel/Regularizer/mulMul7iris_model/input_iris/kernel/Regularizer/mul/x:output:05iris_model/input_iris/kernel/Regularizer/Sum:output:0*
T0*
_output_shapes
: 2.
,iris_model/input_iris/kernel/Regularizer/mull
IdentityIdentitySoftmax:softmax:0^NoOp*
T0*'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ2

IdentityÀ
NoOpNoOp^BiasAdd/ReadVariableOp^MatMul/ReadVariableOp?^iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp*"
_acd_function_control_output(*
_output_shapes
 2
NoOp"
identityIdentity:output:0*(
_construction_contextkEagerRuntime**
_input_shapes
:ÿÿÿÿÿÿÿÿÿ: : 20
BiasAdd/ReadVariableOpBiasAdd/ReadVariableOp2.
MatMul/ReadVariableOpMatMul/ReadVariableOp2
>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp:O K
'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ
 
_user_specified_nameinputs
ä-
Õ
"__inference__traced_restore_125338
file_prefix?
-assignvariableop_iris_model_input_iris_kernel:;
-assignvariableop_1_iris_model_input_iris_bias:%
assignvariableop_2_sgd_iter:	 &
assignvariableop_3_sgd_decay: .
$assignvariableop_4_sgd_learning_rate: )
assignvariableop_5_sgd_momentum: "
assignvariableop_6_total: "
assignvariableop_7_count: $
assignvariableop_8_total_1: $
assignvariableop_9_count_1: 
identity_11¢AssignVariableOp¢AssignVariableOp_1¢AssignVariableOp_2¢AssignVariableOp_3¢AssignVariableOp_4¢AssignVariableOp_5¢AssignVariableOp_6¢AssignVariableOp_7¢AssignVariableOp_8¢AssignVariableOp_9
RestoreV2/tensor_namesConst"/device:CPU:0*
_output_shapes
:*
dtype0*
valueBB$d1/kernel/.ATTRIBUTES/VARIABLE_VALUEB"d1/bias/.ATTRIBUTES/VARIABLE_VALUEB)optimizer/iter/.ATTRIBUTES/VARIABLE_VALUEB*optimizer/decay/.ATTRIBUTES/VARIABLE_VALUEB2optimizer/learning_rate/.ATTRIBUTES/VARIABLE_VALUEB-optimizer/momentum/.ATTRIBUTES/VARIABLE_VALUEB4keras_api/metrics/0/total/.ATTRIBUTES/VARIABLE_VALUEB4keras_api/metrics/0/count/.ATTRIBUTES/VARIABLE_VALUEB4keras_api/metrics/1/total/.ATTRIBUTES/VARIABLE_VALUEB4keras_api/metrics/1/count/.ATTRIBUTES/VARIABLE_VALUEB_CHECKPOINTABLE_OBJECT_GRAPH2
RestoreV2/tensor_names¤
RestoreV2/shape_and_slicesConst"/device:CPU:0*
_output_shapes
:*
dtype0*)
value BB B B B B B B B B B B 2
RestoreV2/shape_and_slicesâ
	RestoreV2	RestoreV2file_prefixRestoreV2/tensor_names:output:0#RestoreV2/shape_and_slices:output:0"/device:CPU:0*@
_output_shapes.
,:::::::::::*
dtypes
2	2
	RestoreV2g
IdentityIdentityRestoreV2:tensors:0"/device:CPU:0*
T0*
_output_shapes
:2

Identity¬
AssignVariableOpAssignVariableOp-assignvariableop_iris_model_input_iris_kernelIdentity:output:0"/device:CPU:0*
_output_shapes
 *
dtype02
AssignVariableOpk

Identity_1IdentityRestoreV2:tensors:1"/device:CPU:0*
T0*
_output_shapes
:2

Identity_1²
AssignVariableOp_1AssignVariableOp-assignvariableop_1_iris_model_input_iris_biasIdentity_1:output:0"/device:CPU:0*
_output_shapes
 *
dtype02
AssignVariableOp_1k

Identity_2IdentityRestoreV2:tensors:2"/device:CPU:0*
T0	*
_output_shapes
:2

Identity_2 
AssignVariableOp_2AssignVariableOpassignvariableop_2_sgd_iterIdentity_2:output:0"/device:CPU:0*
_output_shapes
 *
dtype0	2
AssignVariableOp_2k

Identity_3IdentityRestoreV2:tensors:3"/device:CPU:0*
T0*
_output_shapes
:2

Identity_3¡
AssignVariableOp_3AssignVariableOpassignvariableop_3_sgd_decayIdentity_3:output:0"/device:CPU:0*
_output_shapes
 *
dtype02
AssignVariableOp_3k

Identity_4IdentityRestoreV2:tensors:4"/device:CPU:0*
T0*
_output_shapes
:2

Identity_4©
AssignVariableOp_4AssignVariableOp$assignvariableop_4_sgd_learning_rateIdentity_4:output:0"/device:CPU:0*
_output_shapes
 *
dtype02
AssignVariableOp_4k

Identity_5IdentityRestoreV2:tensors:5"/device:CPU:0*
T0*
_output_shapes
:2

Identity_5¤
AssignVariableOp_5AssignVariableOpassignvariableop_5_sgd_momentumIdentity_5:output:0"/device:CPU:0*
_output_shapes
 *
dtype02
AssignVariableOp_5k

Identity_6IdentityRestoreV2:tensors:6"/device:CPU:0*
T0*
_output_shapes
:2

Identity_6
AssignVariableOp_6AssignVariableOpassignvariableop_6_totalIdentity_6:output:0"/device:CPU:0*
_output_shapes
 *
dtype02
AssignVariableOp_6k

Identity_7IdentityRestoreV2:tensors:7"/device:CPU:0*
T0*
_output_shapes
:2

Identity_7
AssignVariableOp_7AssignVariableOpassignvariableop_7_countIdentity_7:output:0"/device:CPU:0*
_output_shapes
 *
dtype02
AssignVariableOp_7k

Identity_8IdentityRestoreV2:tensors:8"/device:CPU:0*
T0*
_output_shapes
:2

Identity_8
AssignVariableOp_8AssignVariableOpassignvariableop_8_total_1Identity_8:output:0"/device:CPU:0*
_output_shapes
 *
dtype02
AssignVariableOp_8k

Identity_9IdentityRestoreV2:tensors:9"/device:CPU:0*
T0*
_output_shapes
:2

Identity_9
AssignVariableOp_9AssignVariableOpassignvariableop_9_count_1Identity_9:output:0"/device:CPU:0*
_output_shapes
 *
dtype02
AssignVariableOp_99
NoOpNoOp"/device:CPU:0*
_output_shapes
 2
NoOpº
Identity_10Identityfile_prefix^AssignVariableOp^AssignVariableOp_1^AssignVariableOp_2^AssignVariableOp_3^AssignVariableOp_4^AssignVariableOp_5^AssignVariableOp_6^AssignVariableOp_7^AssignVariableOp_8^AssignVariableOp_9^NoOp"/device:CPU:0*
T0*
_output_shapes
: 2
Identity_10f
Identity_11IdentityIdentity_10:output:0^NoOp_1*
T0*
_output_shapes
: 2
Identity_11¢
NoOp_1NoOp^AssignVariableOp^AssignVariableOp_1^AssignVariableOp_2^AssignVariableOp_3^AssignVariableOp_4^AssignVariableOp_5^AssignVariableOp_6^AssignVariableOp_7^AssignVariableOp_8^AssignVariableOp_9*"
_acd_function_control_output(*
_output_shapes
 2
NoOp_1"#
identity_11Identity_11:output:0*)
_input_shapes
: : : : : : : : : : : 2$
AssignVariableOpAssignVariableOp2(
AssignVariableOp_1AssignVariableOp_12(
AssignVariableOp_2AssignVariableOp_22(
AssignVariableOp_3AssignVariableOp_32(
AssignVariableOp_4AssignVariableOp_42(
AssignVariableOp_5AssignVariableOp_52(
AssignVariableOp_6AssignVariableOp_62(
AssignVariableOp_7AssignVariableOp_72(
AssignVariableOp_8AssignVariableOp_82(
AssignVariableOp_9AssignVariableOp_9:C ?

_output_shapes
: 
%
_user_specified_namefile_prefix
Ã
ß
F__inference_iris_model_layer_call_and_return_conditional_losses_125193
x;
)input_iris_matmul_readvariableop_resource:8
*input_iris_biasadd_readvariableop_resource:
identity¢!input_iris/BiasAdd/ReadVariableOp¢ input_iris/MatMul/ReadVariableOp¢>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp®
 input_iris/MatMul/ReadVariableOpReadVariableOp)input_iris_matmul_readvariableop_resource*
_output_shapes

:*
dtype02"
 input_iris/MatMul/ReadVariableOp
input_iris/MatMulMatMulx(input_iris/MatMul/ReadVariableOp:value:0*
T0*'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ2
input_iris/MatMul­
!input_iris/BiasAdd/ReadVariableOpReadVariableOp*input_iris_biasadd_readvariableop_resource*
_output_shapes
:*
dtype02#
!input_iris/BiasAdd/ReadVariableOp­
input_iris/BiasAddBiasAddinput_iris/MatMul:product:0)input_iris/BiasAdd/ReadVariableOp:value:0*
T0*'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ2
input_iris/BiasAdd
input_iris/SoftmaxSoftmaxinput_iris/BiasAdd:output:0*
T0*'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ2
input_iris/Softmaxê
>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOpReadVariableOp)input_iris_matmul_readvariableop_resource*
_output_shapes

:*
dtype02@
>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOpÝ
/iris_model/input_iris/kernel/Regularizer/SquareSquareFiris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp:value:0*
T0*
_output_shapes

:21
/iris_model/input_iris/kernel/Regularizer/Square±
.iris_model/input_iris/kernel/Regularizer/ConstConst*
_output_shapes
:*
dtype0*
valueB"       20
.iris_model/input_iris/kernel/Regularizer/Constò
,iris_model/input_iris/kernel/Regularizer/SumSum3iris_model/input_iris/kernel/Regularizer/Square:y:07iris_model/input_iris/kernel/Regularizer/Const:output:0*
T0*
_output_shapes
: 2.
,iris_model/input_iris/kernel/Regularizer/Sum¥
.iris_model/input_iris/kernel/Regularizer/mul/xConst*
_output_shapes
: *
dtype0*
valueB
 *
×#<20
.iris_model/input_iris/kernel/Regularizer/mul/xô
,iris_model/input_iris/kernel/Regularizer/mulMul7iris_model/input_iris/kernel/Regularizer/mul/x:output:05iris_model/input_iris/kernel/Regularizer/Sum:output:0*
T0*
_output_shapes
: 2.
,iris_model/input_iris/kernel/Regularizer/mulw
IdentityIdentityinput_iris/Softmax:softmax:0^NoOp*
T0*'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ2

IdentityÖ
NoOpNoOp"^input_iris/BiasAdd/ReadVariableOp!^input_iris/MatMul/ReadVariableOp?^iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp*"
_acd_function_control_output(*
_output_shapes
 2
NoOp"
identityIdentity:output:0*(
_construction_contextkEagerRuntime**
_input_shapes
:ÿÿÿÿÿÿÿÿÿ: : 2F
!input_iris/BiasAdd/ReadVariableOp!input_iris/BiasAdd/ReadVariableOp2D
 input_iris/MatMul/ReadVariableOp input_iris/MatMul/ReadVariableOp2
>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp:J F
'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ

_user_specified_namex
ö

F__inference_iris_model_layer_call_and_return_conditional_losses_125114
x#
input_iris_125102:
input_iris_125104:
identity¢"input_iris/StatefulPartitionedCall¢>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp
"input_iris/StatefulPartitionedCallStatefulPartitionedCallxinput_iris_125102input_iris_125104*
Tin
2*
Tout
2*
_collective_manager_ids
 *'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ*$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8 *O
fJRH
F__inference_input_iris_layer_call_and_return_conditional_losses_1251012$
"input_iris/StatefulPartitionedCallÒ
>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOpReadVariableOpinput_iris_125102*
_output_shapes

:*
dtype02@
>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOpÝ
/iris_model/input_iris/kernel/Regularizer/SquareSquareFiris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp:value:0*
T0*
_output_shapes

:21
/iris_model/input_iris/kernel/Regularizer/Square±
.iris_model/input_iris/kernel/Regularizer/ConstConst*
_output_shapes
:*
dtype0*
valueB"       20
.iris_model/input_iris/kernel/Regularizer/Constò
,iris_model/input_iris/kernel/Regularizer/SumSum3iris_model/input_iris/kernel/Regularizer/Square:y:07iris_model/input_iris/kernel/Regularizer/Const:output:0*
T0*
_output_shapes
: 2.
,iris_model/input_iris/kernel/Regularizer/Sum¥
.iris_model/input_iris/kernel/Regularizer/mul/xConst*
_output_shapes
: *
dtype0*
valueB
 *
×#<20
.iris_model/input_iris/kernel/Regularizer/mul/xô
,iris_model/input_iris/kernel/Regularizer/mulMul7iris_model/input_iris/kernel/Regularizer/mul/x:output:05iris_model/input_iris/kernel/Regularizer/Sum:output:0*
T0*
_output_shapes
: 2.
,iris_model/input_iris/kernel/Regularizer/mul
IdentityIdentity+input_iris/StatefulPartitionedCall:output:0^NoOp*
T0*'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ2

Identity´
NoOpNoOp#^input_iris/StatefulPartitionedCall?^iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp*"
_acd_function_control_output(*
_output_shapes
 2
NoOp"
identityIdentity:output:0*(
_construction_contextkEagerRuntime**
_input_shapes
:ÿÿÿÿÿÿÿÿÿ: : 2H
"input_iris/StatefulPartitionedCall"input_iris/StatefulPartitionedCall2
>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp:J F
'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ

_user_specified_namex
õ

+__inference_input_iris_layer_call_fn_125234

inputs
unknown:
	unknown_0:
identity¢StatefulPartitionedCallö
StatefulPartitionedCallStatefulPartitionedCallinputsunknown	unknown_0*
Tin
2*
Tout
2*
_collective_manager_ids
 *'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ*$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8 *O
fJRH
F__inference_input_iris_layer_call_and_return_conditional_losses_1251012
StatefulPartitionedCall{
IdentityIdentity StatefulPartitionedCall:output:0^NoOp*
T0*'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ2

Identityh
NoOpNoOp^StatefulPartitionedCall*"
_acd_function_control_output(*
_output_shapes
 2
NoOp"
identityIdentity:output:0*(
_construction_contextkEagerRuntime**
_input_shapes
:ÿÿÿÿÿÿÿÿÿ: : 22
StatefulPartitionedCallStatefulPartitionedCall:O K
'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ
 
_user_specified_nameinputs
ø

+__inference_iris_model_layer_call_fn_125121
input_1
unknown:
	unknown_0:
identity¢StatefulPartitionedCall÷
StatefulPartitionedCallStatefulPartitionedCallinput_1unknown	unknown_0*
Tin
2*
Tout
2*
_collective_manager_ids
 *'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ*$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8 *O
fJRH
F__inference_iris_model_layer_call_and_return_conditional_losses_1251142
StatefulPartitionedCall{
IdentityIdentity StatefulPartitionedCall:output:0^NoOp*
T0*'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ2

Identityh
NoOpNoOp^StatefulPartitionedCall*"
_acd_function_control_output(*
_output_shapes
 2
NoOp"
identityIdentity:output:0*(
_construction_contextkEagerRuntime**
_input_shapes
:ÿÿÿÿÿÿÿÿÿ: : 22
StatefulPartitionedCallStatefulPartitionedCall:P L
'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ
!
_user_specified_name	input_1
À
«
!__inference__wrapped_model_125077
input_1F
4iris_model_input_iris_matmul_readvariableop_resource:C
5iris_model_input_iris_biasadd_readvariableop_resource:
identity¢,iris_model/input_iris/BiasAdd/ReadVariableOp¢+iris_model/input_iris/MatMul/ReadVariableOpÏ
+iris_model/input_iris/MatMul/ReadVariableOpReadVariableOp4iris_model_input_iris_matmul_readvariableop_resource*
_output_shapes

:*
dtype02-
+iris_model/input_iris/MatMul/ReadVariableOp¶
iris_model/input_iris/MatMulMatMulinput_13iris_model/input_iris/MatMul/ReadVariableOp:value:0*
T0*'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ2
iris_model/input_iris/MatMulÎ
,iris_model/input_iris/BiasAdd/ReadVariableOpReadVariableOp5iris_model_input_iris_biasadd_readvariableop_resource*
_output_shapes
:*
dtype02.
,iris_model/input_iris/BiasAdd/ReadVariableOpÙ
iris_model/input_iris/BiasAddBiasAdd&iris_model/input_iris/MatMul:product:04iris_model/input_iris/BiasAdd/ReadVariableOp:value:0*
T0*'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ2
iris_model/input_iris/BiasAdd£
iris_model/input_iris/SoftmaxSoftmax&iris_model/input_iris/BiasAdd:output:0*
T0*'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ2
iris_model/input_iris/Softmax
IdentityIdentity'iris_model/input_iris/Softmax:softmax:0^NoOp*
T0*'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ2

Identity«
NoOpNoOp-^iris_model/input_iris/BiasAdd/ReadVariableOp,^iris_model/input_iris/MatMul/ReadVariableOp*"
_acd_function_control_output(*
_output_shapes
 2
NoOp"
identityIdentity:output:0*(
_construction_contextkEagerRuntime**
_input_shapes
:ÿÿÿÿÿÿÿÿÿ: : 2\
,iris_model/input_iris/BiasAdd/ReadVariableOp,iris_model/input_iris/BiasAdd/ReadVariableOp2Z
+iris_model/input_iris/MatMul/ReadVariableOp+iris_model/input_iris/MatMul/ReadVariableOp:P L
'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ
!
_user_specified_name	input_1

¸
F__inference_input_iris_layer_call_and_return_conditional_losses_125225

inputs0
matmul_readvariableop_resource:-
biasadd_readvariableop_resource:
identity¢BiasAdd/ReadVariableOp¢MatMul/ReadVariableOp¢>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp
MatMul/ReadVariableOpReadVariableOpmatmul_readvariableop_resource*
_output_shapes

:*
dtype02
MatMul/ReadVariableOps
MatMulMatMulinputsMatMul/ReadVariableOp:value:0*
T0*'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ2
MatMul
BiasAdd/ReadVariableOpReadVariableOpbiasadd_readvariableop_resource*
_output_shapes
:*
dtype02
BiasAdd/ReadVariableOp
BiasAddBiasAddMatMul:product:0BiasAdd/ReadVariableOp:value:0*
T0*'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ2	
BiasAdda
SoftmaxSoftmaxBiasAdd:output:0*
T0*'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ2	
Softmaxß
>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOpReadVariableOpmatmul_readvariableop_resource*
_output_shapes

:*
dtype02@
>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOpÝ
/iris_model/input_iris/kernel/Regularizer/SquareSquareFiris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp:value:0*
T0*
_output_shapes

:21
/iris_model/input_iris/kernel/Regularizer/Square±
.iris_model/input_iris/kernel/Regularizer/ConstConst*
_output_shapes
:*
dtype0*
valueB"       20
.iris_model/input_iris/kernel/Regularizer/Constò
,iris_model/input_iris/kernel/Regularizer/SumSum3iris_model/input_iris/kernel/Regularizer/Square:y:07iris_model/input_iris/kernel/Regularizer/Const:output:0*
T0*
_output_shapes
: 2.
,iris_model/input_iris/kernel/Regularizer/Sum¥
.iris_model/input_iris/kernel/Regularizer/mul/xConst*
_output_shapes
: *
dtype0*
valueB
 *
×#<20
.iris_model/input_iris/kernel/Regularizer/mul/xô
,iris_model/input_iris/kernel/Regularizer/mulMul7iris_model/input_iris/kernel/Regularizer/mul/x:output:05iris_model/input_iris/kernel/Regularizer/Sum:output:0*
T0*
_output_shapes
: 2.
,iris_model/input_iris/kernel/Regularizer/mull
IdentityIdentitySoftmax:softmax:0^NoOp*
T0*'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ2

IdentityÀ
NoOpNoOp^BiasAdd/ReadVariableOp^MatMul/ReadVariableOp?^iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp*"
_acd_function_control_output(*
_output_shapes
 2
NoOp"
identityIdentity:output:0*(
_construction_contextkEagerRuntime**
_input_shapes
:ÿÿÿÿÿÿÿÿÿ: : 20
BiasAdd/ReadVariableOpBiasAdd/ReadVariableOp2.
MatMul/ReadVariableOpMatMul/ReadVariableOp2
>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp>iris_model/input_iris/kernel/Regularizer/Square/ReadVariableOp:O K
'
_output_shapes
:ÿÿÿÿÿÿÿÿÿ
 
_user_specified_nameinputs"¨L
saver_filename:0StatefulPartitionedCall_1:0StatefulPartitionedCall_28"
saved_model_main_op

NoOp*>
__saved_model_init_op%#
__saved_model_init_op

NoOp*«
serving_default
;
input_10
serving_default_input_1:0ÿÿÿÿÿÿÿÿÿ<
output_10
StatefulPartitionedCall:0ÿÿÿÿÿÿÿÿÿtensorflow/serving/predict:î)
é
d1
	optimizer
regularization_losses
	variables
trainable_variables
	keras_api

signatures
*'&call_and_return_all_conditional_losses
(_default_save_signature
)__call__"
_tf_keras_model
»

kernel
	bias

regularization_losses
	variables
trainable_variables
	keras_api
**&call_and_return_all_conditional_losses
+__call__"
_tf_keras_layer
I
iter
	decay
learning_rate
momentum"
	optimizer
'
,0"
trackable_list_wrapper
.
0
	1"
trackable_list_wrapper
.
0
	1"
trackable_list_wrapper
Ê
regularization_losses
layer_metrics
	variables
non_trainable_variables
metrics
layer_regularization_losses

layers
trainable_variables
)__call__
(_default_save_signature
*'&call_and_return_all_conditional_losses
&'"call_and_return_conditional_losses"
_generic_user_object
,
-serving_default"
signature_map
.:,2iris_model/input_iris/kernel
(:&2iris_model/input_iris/bias
'
,0"
trackable_list_wrapper
.
0
	1"
trackable_list_wrapper
.
0
	1"
trackable_list_wrapper
­

regularization_losses
layer_metrics
	variables
non_trainable_variables
metrics
layer_regularization_losses

layers
trainable_variables
+__call__
**&call_and_return_all_conditional_losses
&*"call_and_return_conditional_losses"
_generic_user_object
:	 (2SGD/iter
: (2	SGD/decay
: (2SGD/learning_rate
: (2SGD/momentum
 "
trackable_dict_wrapper
 "
trackable_list_wrapper
.
0
1"
trackable_list_wrapper
 "
trackable_list_wrapper
'
0"
trackable_list_wrapper
 "
trackable_dict_wrapper
 "
trackable_list_wrapper
 "
trackable_list_wrapper
'
,0"
trackable_list_wrapper
 "
trackable_list_wrapper
N
	total
	count
 	variables
!	keras_api"
_tf_keras_metric
^
	"total
	#count
$
_fn_kwargs
%	variables
&	keras_api"
_tf_keras_metric
:  (2total
:  (2count
.
0
1"
trackable_list_wrapper
-
 	variables"
_generic_user_object
:  (2total
:  (2count
 "
trackable_dict_wrapper
.
"0
#1"
trackable_list_wrapper
-
%	variables"
_generic_user_object
³2°
F__inference_iris_model_layer_call_and_return_conditional_losses_125193
F__inference_iris_model_layer_call_and_return_conditional_losses_125155
²
FullArgSpec
args
jself
jx
varargs
 
varkw
 
defaults
 

kwonlyargs 
kwonlydefaults
 
annotationsª *
 
ÌBÉ
!__inference__wrapped_model_125077input_1"
²
FullArgSpec
args 
varargsjargs
varkwjkwargs
defaults
 

kwonlyargs 
kwonlydefaults
 
annotationsª *
 
ý2ú
+__inference_iris_model_layer_call_fn_125121
+__inference_iris_model_layer_call_fn_125202
²
FullArgSpec
args
jself
jx
varargs
 
varkw
 
defaults
 

kwonlyargs 
kwonlydefaults
 
annotationsª *
 
ð2í
F__inference_input_iris_layer_call_and_return_conditional_losses_125225¢
²
FullArgSpec
args
jself
jinputs
varargs
 
varkw
 
defaults
 

kwonlyargs 
kwonlydefaults
 
annotationsª *
 
Õ2Ò
+__inference_input_iris_layer_call_fn_125234¢
²
FullArgSpec
args
jself
jinputs
varargs
 
varkw
 
defaults
 

kwonlyargs 
kwonlydefaults
 
annotationsª *
 
³2°
__inference_loss_fn_0_125245
²
FullArgSpec
args 
varargs
 
varkw
 
defaults
 

kwonlyargs 
kwonlydefaults
 
annotationsª *¢ 
ËBÈ
$__inference_signature_wrapper_125176input_1"
²
FullArgSpec
args 
varargs
 
varkwjkwargs
defaults
 

kwonlyargs 
kwonlydefaults
 
annotationsª *
 
!__inference__wrapped_model_125077k	0¢-
&¢#
!
input_1ÿÿÿÿÿÿÿÿÿ
ª "3ª0
.
output_1"
output_1ÿÿÿÿÿÿÿÿÿ¦
F__inference_input_iris_layer_call_and_return_conditional_losses_125225\	/¢,
%¢"
 
inputsÿÿÿÿÿÿÿÿÿ
ª "%¢"

0ÿÿÿÿÿÿÿÿÿ
 ~
+__inference_input_iris_layer_call_fn_125234O	/¢,
%¢"
 
inputsÿÿÿÿÿÿÿÿÿ
ª "ÿÿÿÿÿÿÿÿÿ§
F__inference_iris_model_layer_call_and_return_conditional_losses_125155]	0¢-
&¢#
!
input_1ÿÿÿÿÿÿÿÿÿ
ª "%¢"

0ÿÿÿÿÿÿÿÿÿ
 ¡
F__inference_iris_model_layer_call_and_return_conditional_losses_125193W	*¢'
 ¢

xÿÿÿÿÿÿÿÿÿ
ª "%¢"

0ÿÿÿÿÿÿÿÿÿ
 
+__inference_iris_model_layer_call_fn_125121P	0¢-
&¢#
!
input_1ÿÿÿÿÿÿÿÿÿ
ª "ÿÿÿÿÿÿÿÿÿy
+__inference_iris_model_layer_call_fn_125202J	*¢'
 ¢

xÿÿÿÿÿÿÿÿÿ
ª "ÿÿÿÿÿÿÿÿÿ;
__inference_loss_fn_0_125245¢

¢ 
ª " 
$__inference_signature_wrapper_125176v	;¢8
¢ 
1ª.
,
input_1!
input_1ÿÿÿÿÿÿÿÿÿ"3ª0
.
output_1"
output_1ÿÿÿÿÿÿÿÿÿ