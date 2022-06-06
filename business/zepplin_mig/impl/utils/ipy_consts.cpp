#include "utils/ipy_consts.h"

std::string ipynb_template = R"(
{
 "cells": [],
 "metadata": {},
 "nbformat": 4,
 "nbformat_minor": 5
})";

std::string cell_template =  R"({
   "cell_type": "code",
   "execution_count": 0,
   "id": "20210811-090428_1531045589",
   "metadata": {},
   "outputs": [
   ],
   "source": [
   ]
  })";

std::string meta_template = R"(
{
  "kernelspec": {
   "display_name": "Python 3",
   "language": "python",
   "name": "python3"
  },
  "language_info": {
   "codemirror_mode": {
    "name": "ipython",
    "version": 3
   },
   "file_extension": ".py",
   "mimetype": "text/x-python",
   "name": "python",
   "nbconvert_exporter": "python",
   "pygments_lexer": "ipython3",
   "version": "3.8.8"
  }
}
)";
