# Notes

Notes on things in the `webgpu.h` header which where confusing, hard, or
strange. (At least to me). In no particular order.

## Lack of documentation
Hard to figure out what methods exist on what, or how to search for them.
Spent a long time trying to figure out what returned a `WGPUAdapter`
until it was pointed out it's a callback method.

## Using a callback to get the adapter.
Most things seem to return the object with a `Create` method (like
`Instance` or `Device`). `Adapter` is different in that there is a
callback method. It does receive extra data, but it seems like this
could be handled with a `WGPUAdapterCreateResult` struct returning the
`WGPURequestAdapterStatus` and the `WGPUAdapter` or something similar.

### Ordering of adapter callback
Initial thought was the callback would be called at some point in the
future, so wasn't sure how to continue engine setup. Testing shows the
callback is executed before the `wgpuInstanceRequestAdaptor` is called,
but wasn't clear that would be the case.

## Method naming switches order
It's `wgpuCreateInstance` but `wgpuInstanceRelease`. The naming flips
order between the create and the methods on the objects.

## `Force32` is ...
The `Force32` entry is added to force enums to 32-bits. Understandable
but annoying with `Wswitch-enum` as you end up adding an empty `Force32`
case statement. Don't know if this is fixable in another way.

## Release of device causes device lost
During cleanup, the `wgpuDeviceRelease` call triggers the `device_lost`
callback. Have to remove the callback before releasing the device. It
seems like an explicit release shouldn't be considered device lost?

## Surface creation is ...
This is better on the C++ side, but doing surface creation in C involves
a bit of hoop jumping (although the code is pretty much all boiler
plate).

## Object life times

### Returned objects
Unsure of the life times of objects. Wasn't sure if a `Retain` was
required after something like a `wgpuCreateInstance` call

#### Resolved
kangz confirmed it is not required to `Retain` on creation as the
objects are retained by default.

### Other lifetimes
What is the lifetime of things like strings passed in for labels? Just
the call, life of adapter?

## Missing `SetLabel` methods?
Some objects currently accept a `label` in the descriptor, but have no
`SetLabel` method. Was initially confused as I was doing `SetLabel` all
the time and it didn't always compile.
