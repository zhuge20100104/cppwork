# Training [TensorFlow](https://www.tensorflow.org) models in C++

Python is the primary language in which TensorFlow models are typically developed and trained.
TensorFlow does have [bindings for other programming languages](https://www.tensorflow.org/api_docs/).
These bindings have the low-level primitives that are required to build a more complete API, however, lack
much of the higher-level API richness of the Python bindings, particularly for defining the model structure.

This file demonstrates taking a model (a TensorFlow graph) created by a Python program and running the training loop
in C++.

## The model

The model is a trivial one, trying to learn the function: `f(x) = W\*x + b`, where `W` and `b` are model parameters.
The training data is constructed so that the "true" value of `W` is 3 and that of `b` is 2, i.e., `f(x) = 3 * x + 2`.

## Files

- `model.py`: Python code that constructs a model and saves the computational graph in file called `graph.pb`. TAll other files assume that `model.py` has been run once.
- `train.cc`: C++ code that loads the model, optionally loads model weights saved in a checkpoint, trains a few steps, writes the updated model weights to a checkpoint.

## Noteworthy

- The Python APIs for TensorFlow include other conveniences for training (such as `MonitoredSession` and `tf.train.Estimator`), which make it easier to configure checkpointing, evaluation loops etc. The examples here aren't that sophisticated and are focused on basic model training only.
- In this example, we use placeholders and feed dictionaries to feed input, but in a real example you probably want to use the [`tf.data`](https://www.tensorflow.org/programmers_guide/datasets) API to cconstruct an input pipeline for providing training data to the model.
- Not demonstrated here, but summaries for TensorBoard can also be produced by executing the summary operations.

## See Also

- [Training in C](https://gist.github.com/asimshankar/7c9f8a9b04323e93bb217109da8c7ad2)