classdef Signal < Simulink.Signal
%SimulinkDemos.Signal  Class definition.

%   Copyright 2009-2017 The MathWorks, Inc.

  properties
    GenericProperty = [];
  end
  
  properties(PropertyType = 'double scalar')
    DoubleProperty = 0;
  end

  properties(PropertyType = 'int32 scalar')
    Int32Property = int32(0);
  end
  
  properties(PropertyType = 'logical scalar')
    LogicalProperty = false;
  end
  
  properties(PropertyType = 'char')
    CharProperty = '';
  end
  
  properties(PropertyType = 'char', AllowedValues = {'on'; 'off'})
    OnOffCharProperty = 'off';
  end
  
  properties(PropertyType = 'char', ...
             AllowedValues = {'red'; 'green'; 'blue'; 'white'; 'black'})
    ColorCharProperty = 'red';
  end

  %---------------------------------------------------------------------------
  % NOTE:
  % -----
  % By default this class will use the custom storage classes from its
  % superclass.  To define your own custom storage classes:
  % - Uncomment the following method and specify the correct package name.
  % - Launch the cscdesigner for this package.
  %     >> cscdesigner('packageName');
  %
  % methods
  %   function setupCoderInfo(h)
  %     % Use custom storage classes from this package
  %     useLocalCustomStorageClasses(h, 'packageName');
  %   end
  % end % methods
  
  methods
    %---------------------------------------------------------------------------
    function h = Signal(varargin)
      % SIGNAL  Class constructor.
          
      % Call superclass constructor with variable arguments
      h@Simulink.Signal(varargin{:});
    end
  end
  
  methods (Access=protected)
    %---------------------------------------------------------------------------
    function retVal = copyElement(obj)
    %COPYELEMENT  Define special copy behavior for properties of this class.
    %             See matlab.mixin.Copyable for more details.
      retVal = copyElement@Simulink.Signal(obj);
      if isobject(obj.GenericProperty)
        retVal.GenericProperty = copy(obj.GenericProperty);
      end
    end
  end
  
end % classdef
